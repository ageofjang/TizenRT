/****************************************************************************
 *
 * Copyright 2016 Samsung Electronics All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
 * either express or implied. See the License for the specific
 * language governing permissions and limitations under the License.
 *
 ****************************************************************************/
/****************************************************************************
 * include/tinyara/analog/adc.h
 *
 *   Copyright (C) 2016-2017 Gregory Nutt. All rights reserved.
 *   Copyright (C) 2011 Li Zhuoyi. All rights reserved.
 *   Author: Li Zhuoyi <lzyy.cn@gmail.com>
 *           Gregory Nutt <gnutt@nuttx.org>
 *
 * Derived from include/tinyara/drivers/can.h
 *
 *   Copyright (C) 2008, 2009 Gregory Nutt. All rights reserved.
 *   Author: Gregory Nutt <gnutt@nuttx.org>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name NuttX nor the names of its contributors may be
 *    used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 ****************************************************************************/

#ifndef __INCLUDE_TINYARA_ANALOG_ADC_H
#define __INCLUDE_TINYARA_ANALOG_ADC_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <tinyara/config.h>
#include <tinyara/compiler.h>

#include <sys/types.h>
#include <stdint.h>
#include <stdbool.h>
#include <semaphore.h>
#include <tinyara/fs/fs.h>
#include <tinyara/spi/spi.h>

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/*
 * Default configuration settings that may be overridden in the TinyARA
 * configuration file. The configured size is limited to 255 to fit into
 * a uint8_t.
 */

#if !defined(CONFIG_ADC_FIFOSIZE)
#define CONFIG_ADC_FIFOSIZE 8
#elif CONFIG_ADC_FIFOSIZE > 255
#undef  CONFIG_ADC_FIFOSIZE
#define CONFIG_ADC_FIFOSIZE 255
#endif

#define ADC_RESET(dev)         ((dev)->ad_ops->ao_reset((dev)))
#define ADC_SETUP(dev)         ((dev)->ad_ops->ao_setup((dev)))
#define ADC_SHUTDOWN(dev)      ((dev)->ad_ops->ao_shutdown((dev)))
#define ADC_RXINT(dev)         ((dev)->ad_ops->ao_rxint((dev)))
#define ADC_IOCTL(dev,cmd,arg) ((dev)->ad_ops->ao_ioctl((dev),(cmd),(arg)))

/****************************************************************************
 * Public Types
 ****************************************************************************/
/* These are callbacks to notify the upper-half driver of ADC events */

struct adc_dev_s;
struct adc_callback_s {
	/*
	 * This method is called from the lower half, platform-specific ADC
	 * logic when new ADC sample data is available.
	 *
	 * Input Parameters:
	 *   dev  - The ADC device structure that was previously registered
	 *          by adc_register()
	 *   ch   - And ID for the ADC channel number that generated the data
	 *   data - The actual converted data from the channel.
	 *
	 * Returned Value:
	 *   Zero on success; a negated errno value on failure.
	 */

	CODE int (*au_receive)(FAR struct adc_dev_s *dev, uint8_t ch,
			       int32_t data);
};

/* This describes on ADC message */

struct adc_msg_s {
	uint8_t am_channel;	/* The 8-bit ADC Channel */
	int32_t am_data;	/* ADC convert result (4 bytes) */
} packed_struct;

/* This describes a FIFO of ADC messages */

struct adc_fifo_s {
	sem_t   af_sem;		/* Counting semaphore */
	uint8_t af_head;	/* Index to the head [IN] index in the circular buffer */
	uint8_t af_tail;	/* Index to the tail [OUT] index in the circular buffer */
	/* Circular buffer of CAN messages */
	struct  adc_msg_s af_buffer[CONFIG_ADC_FIFOSIZE];
};

/*
 * This structure defines all of the operations providd by the architecture
 * specific logic. All fields must be provided with non-NULL function pointers
 * by the caller of can_register().
 */

struct adc_dev_s;
struct adc_ops_s {
	/*
	 * Bind the upper-half driver callbacks to the lower-half
	 * implementation. This must be called early in order to receive ADC
	 * event notifications.
	 */

	CODE int (*ao_bind)(FAR struct adc_dev_s *dev,
			FAR const struct adc_callback_s *callback);

	/*
	 * Reset the ADC device.  Called early to initialize the hardware.
	 * This is called, before ao_setup() and on error conditions.
	 */

	CODE void (*ao_reset)(FAR struct adc_dev_s *dev);

	/*
	 * Configure the ADC. This method is called the first time that the
	 * ADC device is opened.  This will occur when the port is first
	 * opened. This setup includes configuring and attaching ADC
	 * interrupts. Interrupts are all disabled upon return.
	 */

	CODE int (*ao_setup)(FAR struct adc_dev_s *dev);

	/*
	 * Disable the ADC. This method is called when the ADC device is
	 * closed. This method reverses the operation the setup method.
	 */

	CODE void (*ao_shutdown)(FAR struct adc_dev_s *dev);

	/* Call to enable or disable RX interrupts */

	CODE void (*ao_rxint)(FAR struct adc_dev_s *dev, bool enable);

	/* All ioctl calls will be routed through this method */

	CODE int (*ao_ioctl)(FAR struct adc_dev_s *dev, int cmd, unsigned long arg);
};

/*
 * This is the device structure used by the driver.  The caller of
 * adc_register() must allocate and initialize this structure.  The calling
 * logic need only set all fields to zero except:
 *
 *   The elements of 'ad_ops', and 'ad_priv'
 *
 * The common logic will initialize all semaphores.
 */

struct adc_dev_s {
#ifdef CONFIG_ADC
	/* Fields managed by common upper half ADC logic */

	uint8_t           ad_ocount;     /* The number of times the device has been opened */
	uint8_t           ad_nrxwaiters; /* Number of threads waiting to enqueue a message */
	sem_t             ad_closesem;   /* Locks out new opens while close is in progress */
	sem_t             ad_recvsem;    /* Used to wakeup user waiting for space in ad_recv.buffer */
	struct adc_fifo_s ad_recv;       /* Describes receive FIFO */
#endif

	/* Fields provided by lower half ADC logic */

	FAR const struct adc_ops_s *ad_ops;  /* Arch-specific operations */
	FAR void                   *ad_priv; /* Used by the arch-specific logic */
};

/****************************************************************************
 * Public Function Prototypes
 ****************************************************************************/

#if defined(__cplusplus)
extern "C"
{
#endif

/****************************************************************************
 * "Upper-Half" ADC Driver Interfaces
 ****************************************************************************/

/****************************************************************************
 * Name: adc_register
 *
 * Description:
 *   Register a ADC driver. This function binds an instance of a "lower half"
 *   ADC driver with the "upper half" ADC device and registers that device so
 *   that can be used by application code.
 *
 * Input parameters:
 *   path - The full path to the driver to be registers in the TinyARA
 *     pseudo-filesystem. The recommended convention is to name all PWM
 *     drivers as "/dev/adc", "/dev/adc1", etc.  where the driver path differs
 *     only in the "minor" number at the end of the device name.
 *   dev - A pointer to an instance of lower half ADC driver.  This instance
 *     is bound to the upper half ADC driver and must persists as long as the
 *     upper half driver driver persists.
 *
 * Returned Value:
 *   Zero on success; a negated errno value on failure.
 *
 ****************************************************************************/

int adc_register(FAR const char *path, FAR struct adc_dev_s *dev);

/****************************************************************************
 * Platform-Independent "Lower Half" ADC Driver Interfaces
 ****************************************************************************/

/****************************************************************************
 * Name: up_ads1255initialize
 *
 * Description:
 *   Initialize the TI ADS 125X lower half driver
 *
 ****************************************************************************/

FAR struct adc_dev_s *up_ads1255initialize(FAR struct spi_dev_s *spi,
		unsigned int devno);

#if defined(__cplusplus)
}
#endif

#endif /* __INCLUDE_TINYARA_ANALOG_ADC_H */
