/****************************************************************************
 *
 * Copyright 2018 Samsung Electronics All Rights Reserved.
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
 * examples/security_sdk/security_sdk_setkey.c
 *
 *   Copyright (C) 2018 SAMSUNG ELECTRONICS CO., LTD. All rights reserved.
 *   Author: Youngdae Oh <yd.oh@samsung.com>
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

#include <security_sdk_test.h>

#define SEE_REMOVE_KEY_TC 5

unsigned char rsa2048_sample[1191] = {
	0x30, 0x82, 0x04, 0xa3, 0x02, 0x01, 0x01, 0x02, 0x82, 0x01, 0x01, 0x00, 0xa2, 0x64, 0x21, 0xcf,
	0x1c, 0xdb, 0x49, 0x6c, 0x44, 0x01, 0xf8, 0xd5, 0x8b, 0x8d, 0x20, 0xfe, 0x2a, 0x46, 0x4d, 0x29,
	0xf4, 0x82, 0x3c, 0xa4, 0x29, 0x7d, 0x6b, 0xdc, 0xc4, 0x04, 0xd6, 0x0f, 0xf3, 0x6b, 0xa8, 0xb1,
	0xad, 0x2b, 0xa1, 0xa5, 0xad, 0xfb, 0x9a, 0xba, 0x72, 0x6e, 0x4e, 0x71, 0x93, 0x54, 0x8d, 0x90,
	0x02, 0x34, 0x80, 0x1d, 0x8c, 0x83, 0xc9, 0x84, 0xa3, 0xcf, 0x9f, 0x80, 0xe9, 0x4f, 0x5b, 0xf6,
	0x29, 0x17, 0xf6, 0x7f, 0x5a, 0x79, 0x47, 0x0c, 0x2c, 0xcf, 0x98, 0x88, 0x6a, 0x31, 0x4e, 0x0a,
	0x2c, 0x8e, 0x8c, 0xe5, 0xa5, 0x9f, 0xd7, 0x8f, 0xd0, 0xc1, 0x04, 0x1a, 0xe9, 0x54, 0xa1, 0x36,
	0x4e, 0x92, 0x5e, 0x41, 0x9c, 0x07, 0xc8, 0x48, 0xac, 0x9c, 0x7c, 0xcb, 0xa0, 0x8a, 0x51, 0x52,
	0x4f, 0x47, 0xa2, 0xc8, 0x48, 0xbc, 0xcd, 0x55, 0x85, 0x24, 0xff, 0xfa, 0x58, 0xe6, 0x75, 0x61,
	0x14, 0x1a, 0x82, 0x4e, 0x6b, 0x40, 0x63, 0x9e, 0xef, 0xbd, 0x70, 0x88, 0x9e, 0xc8, 0x59, 0x89,
	0x16, 0x0c, 0x4e, 0x71, 0xec, 0x2d, 0xa4, 0x0b, 0xb3, 0x20, 0xca, 0x04, 0x5b, 0x37, 0xf6, 0x5c,
	0x80, 0x8d, 0x6a, 0xe4, 0x26, 0x95, 0xe4, 0xd5, 0x35, 0xcd, 0xd3, 0x90, 0x67, 0x48, 0xef, 0x14,
	0x8e, 0xc6, 0xcc, 0x16, 0xdb, 0x7a, 0x96, 0xd6, 0xbf, 0x01, 0xef, 0x5f, 0x8d, 0xee, 0x35, 0xd1,
	0x66, 0xa3, 0x26, 0x96, 0x5e, 0x73, 0x3b, 0x1e, 0xf6, 0x72, 0xc9, 0x78, 0xc8, 0xdd, 0x81, 0x21,
	0x0f, 0x0d, 0xdc, 0x3f, 0x63, 0x7a, 0x92, 0xf1, 0x31, 0x53, 0xe6, 0x34, 0xd7, 0x70, 0xb0, 0x1d,
	0x2f, 0x97, 0xab, 0x44, 0xf1, 0x70, 0x58, 0x0e, 0xca, 0xab, 0x26, 0x23, 0x39, 0x6e, 0xdb, 0xf5,
	0x5a, 0x15, 0x4a, 0x09, 0x00, 0x7c, 0xe5, 0x82, 0x78, 0xb8, 0xf0, 0xd1, 0x02, 0x01, 0x03, 0x02,
	0x82, 0x01, 0x00, 0x6c, 0x42, 0xc1, 0x34, 0xbd, 0xe7, 0x86, 0x48, 0x2d, 0x56, 0xa5, 0xe3, 0xb2,
	0x5e, 0x15, 0xfe, 0xc6, 0xd9, 0x88, 0xc6, 0xa3, 0x01, 0x7d, 0xc2, 0xc6, 0x53, 0x9d, 0x3d, 0xd8,
	0x03, 0x39, 0x5f, 0xf7, 0x9d, 0x1b, 0x21, 0x1e, 0x1d, 0x16, 0x6e, 0x73, 0xfd, 0x11, 0xd1, 0xa1,
	0x9e, 0xde, 0xf6, 0x62, 0x38, 0x5e, 0x60, 0x01, 0x78, 0x55, 0x69, 0x08, 0x57, 0xdb, 0xad, 0xc2,
	0x8a, 0x6a, 0x55, 0xf0, 0xdf, 0x92, 0xa4, 0x1b, 0x65, 0x4e, 0xff, 0x91, 0xa6, 0x2f, 0x5d, 0x73,
	0x35, 0x10, 0x5a, 0xf1, 0x76, 0x34, 0x06, 0xc8, 0x5f, 0x08, 0x99, 0x19, 0x15, 0x3a, 0x5f, 0xe0,
	0x80, 0xad, 0x67, 0x46, 0x38, 0x6b, 0x79, 0x89, 0xb6, 0xe9, 0x81, 0x12, 0xaf, 0xda, 0xdb, 0x1d,
	0xbd, 0xa8, 0x87, 0xc0, 0x5c, 0x36, 0x36, 0xdf, 0x85, 0x17, 0x30, 0x30, 0x7d, 0xde, 0x39, 0x03,
	0x6d, 0xff, 0xfb, 0x2b, 0x5d, 0x42, 0x90, 0x42, 0x03, 0x55, 0xf6, 0xd1, 0xc3, 0xdd, 0x2c, 0xe5,
	0x94, 0x83, 0xf7, 0x35, 0xb8, 0x05, 0xcd, 0xf5, 0xa5, 0xe6, 0x3b, 0xd1, 0xd2, 0x49, 0xe2, 0xbe,
	0x58, 0x7b, 0x6c, 0xc7, 0xd5, 0xf7, 0x36, 0xe4, 0x00, 0xa4, 0xd6, 0xe9, 0xf6, 0x62, 0x19, 0x36,
	0x58, 0xfb, 0xb4, 0x17, 0x0e, 0x97, 0x9a, 0xba, 0xaa, 0x7d, 0xbd, 0x90, 0xf5, 0x2c, 0x39, 0xeb,
	0x86, 0x26, 0xd5, 0xea, 0xbd, 0xcf, 0xf4, 0x8f, 0x5a, 0xa6, 0x76, 0xde, 0xa7, 0x70, 0x2f, 0x1a,
	0x1e, 0xff, 0x40, 0x39, 0x4d, 0xc0, 0x9f, 0xaa, 0x0a, 0x99, 0x08, 0x68, 0x97, 0x96, 0xb1, 0xb7,
	0x36, 0xe1, 0x46, 0xd5, 0xd6, 0xd0, 0xd1, 0x8f, 0x23, 0x52, 0x19, 0xb8, 0xfd, 0xd1, 0x47, 0xf4,
	0xb2, 0x0d, 0x99, 0xb7, 0x7a, 0xd2, 0x57, 0x01, 0xde, 0x36, 0x69, 0x53, 0x9f, 0xb6, 0x56, 0xa0,
	0x61, 0x89, 0x4b, 0x02, 0x81, 0x81, 0x00, 0xcf, 0xac, 0xb0, 0x32, 0xdc, 0xa1, 0x1a, 0xb7, 0xc6,
	0xe3, 0xb8, 0xde, 0x0a, 0x70, 0x4b, 0xfa, 0x59, 0xa2, 0x0b, 0x6b, 0x2b, 0xe6, 0x5c, 0xd6, 0xe4,
	0xc8, 0xc9, 0xe5, 0xe8, 0xb7, 0xa5, 0xa3, 0x94, 0xcb, 0x55, 0x74, 0x4e, 0xfe, 0xdf, 0x82, 0x97,
	0xd0, 0x36, 0xee, 0x00, 0x03, 0x8e, 0x86, 0x28, 0xa1, 0x10, 0xd5, 0xf9, 0x91, 0x0b, 0x7a, 0x3f,
	0x4e, 0x11, 0xdc, 0x44, 0x39, 0xbe, 0xc2, 0x4c, 0x10, 0xaf, 0x76, 0xa4, 0xe2, 0xf6, 0xd2, 0x5a,
	0x59, 0x69, 0xbb, 0x42, 0xb4, 0x65, 0x50, 0xc8, 0xd8, 0x18, 0x44, 0x55, 0x26, 0x66, 0x8d, 0xd4,
	0x6e, 0x9d, 0x42, 0xe7, 0xac, 0x44, 0x3a, 0x4b, 0x4d, 0x71, 0x46, 0x94, 0x05, 0x19, 0x9b, 0x8f,
	0xdc, 0x25, 0x06, 0xef, 0x00, 0xd2, 0xd5, 0x78, 0xe8, 0xf0, 0x9e, 0xdd, 0x2f, 0xf6, 0xa8, 0x54,
	0xdf, 0xb7, 0x34, 0xe3, 0x5d, 0xc9, 0x55, 0x02, 0x81, 0x81, 0x00, 0xc8, 0x2d, 0xe1, 0x55, 0xd4,
	0x74, 0x66, 0xa4, 0x69, 0xb6, 0xde, 0xfd, 0x8c, 0xee, 0x5e, 0x9b, 0x74, 0x92, 0x45, 0x68, 0xf9,
	0xad, 0x18, 0x41, 0x4c, 0xa9, 0x6b, 0x51, 0xac, 0xe4, 0x6b, 0x3d, 0x9a, 0xab, 0xae, 0x15, 0xdb,
	0x8d, 0x94, 0x1f, 0x2f, 0xd4, 0x1a, 0xc1, 0x64, 0x44, 0xcb, 0x7c, 0x1c, 0x11, 0xfa, 0xd6, 0x7d,
	0x36, 0x04, 0x00, 0x42, 0xbc, 0xc2, 0xa3, 0x99, 0x7e, 0xf6, 0x5c, 0x61, 0xc0, 0xce, 0x6b, 0xea,
	0xb8, 0x36, 0x11, 0xb6, 0x1e, 0xa9, 0x1d, 0x0c, 0x8f, 0xe5, 0x47, 0xaa, 0x10, 0xc7, 0xed, 0x3a,
	0xd7, 0x90, 0x24, 0xf2, 0x28, 0x93, 0xa3, 0xb6, 0xd5, 0x50, 0x10, 0x4b, 0x61, 0x05, 0x9c, 0x44,
	0xdd, 0x96, 0x82, 0xcc, 0x17, 0x79, 0x1b, 0xec, 0x9f, 0x3e, 0xe7, 0x2d, 0x4d, 0xaf, 0xd3, 0xfa,
	0x18, 0x01, 0xc2, 0xae, 0x2d, 0x9c, 0xcb, 0xa4, 0xc8, 0xd9, 0x8d, 0x02, 0x81, 0x81, 0x00, 0x8a,
	0x73, 0x20, 0x21, 0xe8, 0x6b, 0x67, 0x25, 0x2f, 0x42, 0x7b, 0x3e, 0xb1, 0xa0, 0x32, 0xa6, 0xe6,
	0x6c, 0x07, 0x9c, 0xc7, 0xee, 0xe8, 0x8f, 0x43, 0x30, 0x86, 0x99, 0x45, 0xcf, 0xc3, 0xc2, 0x63,
	0x32, 0x38, 0xf8, 0x34, 0xa9, 0xea, 0x57, 0x0f, 0xe0, 0x24, 0x9e, 0xaa, 0xad, 0x09, 0xae, 0xc5,
	0xc0, 0xb5, 0xe3, 0xfb, 0xb6, 0x07, 0xa6, 0xd4, 0xde, 0xb6, 0x92, 0xd8, 0x26, 0x7f, 0x2c, 0x32,
	0xb5, 0xca, 0x4f, 0x18, 0x97, 0x4f, 0x36, 0xe6, 0xe6, 0x46, 0x7c, 0xd7, 0x22, 0xee, 0x35, 0xdb,
	0x3a, 0xba, 0xd8, 0x38, 0xc4, 0x44, 0x5e, 0x8d, 0x9f, 0x13, 0x81, 0xef, 0xc8, 0x2d, 0x7c, 0x32,
	0x33, 0xa0, 0xd9, 0xb8, 0x03, 0x66, 0x67, 0xb5, 0x3d, 0x6e, 0x04, 0x9f, 0x55, 0xe1, 0xe3, 0xa5,
	0xf0, 0xa0, 0x69, 0xe8, 0xca, 0xa4, 0x70, 0x38, 0x95, 0x24, 0xcd, 0xec, 0xe9, 0x30, 0xe3, 0x02,
	0x81, 0x81, 0x00, 0x85, 0x73, 0xeb, 0x8e, 0x8d, 0xa2, 0xef, 0x18, 0x46, 0x79, 0xe9, 0xfe, 0x5d,
	0xf4, 0x3f, 0x12, 0x4d, 0xb6, 0xd8, 0xf0, 0xa6, 0x73, 0x65, 0x80, 0xdd, 0xc6, 0x47, 0x8b, 0xc8,
	0x98, 0x47, 0x7e, 0x67, 0x1d, 0x1e, 0xb9, 0x3d, 0x09, 0x0d, 0x6a, 0x1f, 0xe2, 0xbc, 0x80, 0xed,
	0x83, 0x32, 0x52, 0xbd, 0x61, 0x51, 0xe4, 0x53, 0x79, 0x58, 0x00, 0x2c, 0x7d, 0xd7, 0x17, 0xbb,
	0xa9, 0xf9, 0x92, 0xeb, 0xd5, 0xde, 0xf2, 0x9c, 0x7a, 0xce, 0xb6, 0x79, 0x69, 0xc6, 0x13, 0x5d,
	0xb5, 0x43, 0x85, 0x1c, 0x0b, 0x2f, 0xf3, 0x7c, 0x8f, 0xb5, 0x6d, 0xf6, 0xc5, 0xb7, 0xc2, 0x79,
	0xe3, 0x8a, 0xb5, 0x87, 0x96, 0x03, 0xbd, 0x83, 0x3e, 0x64, 0x57, 0x32, 0xba, 0x50, 0xbd, 0x48,
	0x6a, 0x29, 0xef, 0x73, 0x89, 0x1f, 0xe2, 0xa6, 0xba, 0xab, 0xd7, 0x1e, 0xc9, 0x13, 0x32, 0x6d,
	0xdb, 0x3b, 0xb3, 0x02, 0x81, 0x81, 0x00, 0xa9, 0xe4, 0xa3, 0x54, 0x03, 0x2f, 0xc2, 0x8d, 0xa2,
	0x1e, 0xae, 0xe0, 0xfb, 0xe9, 0xba, 0xe0, 0xb5, 0xb6, 0x69, 0x0d, 0xe3, 0x8e, 0xeb, 0x0a, 0x29,
	0x9d, 0x15, 0xc2, 0x8a, 0x76, 0x96, 0x4e, 0x77, 0xea, 0x1a, 0x0b, 0xe8, 0x9b, 0x5d, 0xf7, 0xbd,
	0x86, 0xfb, 0xe4, 0x6b, 0x3c, 0x32, 0xc6, 0x7a, 0xfe, 0xf7, 0x5f, 0xec, 0x2e, 0x24, 0xfa, 0x68,
	0xac, 0xf2, 0xa5, 0x32, 0x4d, 0xd8, 0xd3, 0x68, 0xfa, 0xde, 0xcc, 0x37, 0x38, 0xa8, 0x3b, 0x4e,
	0xeb, 0xae, 0x25, 0xca, 0xb7, 0xc0, 0x80, 0x70, 0x58, 0xea, 0xc3, 0x52, 0xaa, 0x24, 0x3c, 0x24,
	0x17, 0x47, 0x37, 0x70, 0xf9, 0x45, 0x83, 0x20, 0xce, 0x92, 0xe2, 0x6b, 0x58, 0xfd, 0xa2, 0x90,
	0x5b, 0x68, 0x4c, 0x7e, 0x1a, 0x9b, 0xcd, 0x94, 0xef, 0x4b, 0xe8, 0x8d, 0x9b, 0xf8, 0x38, 0x6e,
	0x1e, 0x12, 0xa5, 0xaf, 0xd3, 0xf0, 0xbd
};

unsigned char rsa1024_sample[609] = {
	0x30, 0x82, 0x02, 0x5B, 0x02, 0x01, 0x00, 0x02, 0x81, 0x81, 0x00, 0xC1, 0x62, 0xAF, 0x64, 0x69,
	0xEB, 0x4A, 0x2E, 0x37, 0x98, 0xA1, 0x3B, 0x1D, 0xA8, 0xD7, 0xFD, 0xA8, 0xDC, 0xB4, 0x31, 0xCE,
	0xD2, 0xB9, 0x48, 0x29, 0x21, 0x92, 0xC7, 0xE5, 0x8D, 0xA7, 0xCD, 0x15, 0xEA, 0xB9, 0x41, 0x87,
	0xAA, 0xB9, 0x08, 0x07, 0x69, 0x3A, 0x28, 0xC7, 0x28, 0x28, 0xE9, 0x3C, 0x85, 0x61, 0x13, 0xAC,
	0xBB, 0x01, 0x35, 0xE8, 0xC5, 0xF3, 0x91, 0x4C, 0x2C, 0x3D, 0xE1, 0xD5, 0xF8, 0x4B, 0xA0, 0x28,
	0xE2, 0x4A, 0x6B, 0x07, 0xBF, 0x4D, 0xDD, 0x5F, 0x3F, 0xDC, 0x1C, 0x9A, 0xF5, 0xCD, 0xDC, 0x7B,
	0xAD, 0xB5, 0x8C, 0x15, 0x4A, 0x77, 0xEC, 0x0F, 0x91, 0x0C, 0xEF, 0x57, 0x85, 0x82, 0xE3, 0x9A,
	0x1A, 0x46, 0x6B, 0x67, 0xA7, 0x3C, 0xEB, 0xA7, 0xDF, 0x60, 0xB5, 0xDA, 0xAB, 0x9B, 0xEF, 0xA0,
	0xCB, 0xBD, 0x0E, 0x82, 0x32, 0x15, 0x44, 0xB9, 0xBC, 0x5F, 0x05, 0x02, 0x03, 0x01, 0x00, 0x01,
	0x02, 0x81, 0x80, 0x1D, 0x0D, 0xAC, 0x78, 0x13, 0x89, 0xAB, 0xED, 0x61, 0xA0, 0xE6, 0xA8, 0x30,
	0xFE, 0x8A, 0xE4, 0xAB, 0x17, 0xED, 0x62, 0x86, 0x46, 0x16, 0x5C, 0x07, 0x01, 0xEA, 0x41, 0x69,
	0xF5, 0x6C, 0x3E, 0x5D, 0x8A, 0x94, 0x26, 0x8A, 0x31, 0x55, 0xF7, 0x24, 0xD5, 0xE4, 0x4C, 0xF8,
	0x0E, 0xCA, 0x86, 0xAF, 0xF7, 0x01, 0xEC, 0xA8, 0xC8, 0xB7, 0x97, 0xD7, 0xCE, 0xD5, 0x97, 0x00,
	0xB0, 0xAC, 0xE3, 0x1B, 0xD1, 0xAD, 0x98, 0xEC, 0x7C, 0x44, 0x96, 0xD2, 0xDD, 0x0C, 0x85, 0x22,
	0x07, 0xF4, 0xCC, 0x7A, 0x38, 0x82, 0x18, 0x79, 0xC8, 0x71, 0x15, 0x67, 0xB6, 0xAB, 0x07, 0xB9,
	0xC7, 0x95, 0xE7, 0x0D, 0x4A, 0xE9, 0x8E, 0x6A, 0x78, 0xB4, 0xCB, 0x47, 0xB8, 0xC1, 0x35, 0x0E,
	0xB3, 0xD0, 0xB9, 0x64, 0xCF, 0xFF, 0x08, 0xDB, 0x86, 0xB2, 0x05, 0x7D, 0xB6, 0x11, 0xE8, 0x35,
	0xBA, 0x92, 0xC9, 0x02, 0x41, 0x00, 0xF4, 0x67, 0xC2, 0xC8, 0x3F, 0xF2, 0x68, 0xDD, 0xFA, 0x21,
	0xE5, 0xCD, 0x8F, 0xFA, 0xFA, 0xFE, 0x42, 0xBA, 0x93, 0x42, 0x7A, 0x72, 0x5C, 0x54, 0xC3, 0xEE,
	0x98, 0x4C, 0x7F, 0x60, 0xAB, 0x08, 0x96, 0xDC, 0x3D, 0xDC, 0xB7, 0xDC, 0x2E, 0xB5, 0xC3, 0xB9,
	0xA0, 0x5A, 0x12, 0xAE, 0x61, 0xFD, 0x86, 0x7C, 0xAC, 0x0C, 0x26, 0xD8, 0xC5, 0x86, 0x41, 0x5C,
	0xF6, 0x10, 0xA0, 0xFA, 0x3F, 0xA7, 0x02, 0x41, 0x00, 0xCA, 0x8F, 0x4D, 0x3C, 0x1D, 0x02, 0xC8,
	0x0A, 0xCE, 0x2D, 0x5C, 0x5B, 0x5A, 0x3D, 0x29, 0x63, 0x6D, 0x5E, 0xBC, 0xBB, 0xE9, 0x99, 0x7F,
	0xDB, 0x4E, 0xC1, 0xC6, 0x99, 0xC5, 0x24, 0xCB, 0x64, 0xFA, 0xBF, 0x3E, 0x70, 0xB4, 0x66, 0x91,
	0x7E, 0xEC, 0x0D, 0x69, 0x74, 0xEE, 0xC4, 0x1E, 0xC5, 0xE9, 0xC0, 0xE8, 0x46, 0x36, 0x19, 0x82,
	0xE3, 0xBA, 0xC9, 0x2B, 0xEF, 0xB9, 0xA0, 0xE1, 0x73, 0x02, 0x40, 0x1F, 0xEB, 0x39, 0x2E, 0x0B,
	0xE3, 0xED, 0xBC, 0x27, 0xC1, 0xAB, 0x90, 0x78, 0x20, 0x50, 0x0D, 0x4A, 0xCB, 0xB1, 0x15, 0xBA,
	0x86, 0x1A, 0xF6, 0xDB, 0x0B, 0xDB, 0x0A, 0x0A, 0x8C, 0xA6, 0x69, 0x9D, 0xC2, 0x2F, 0xB6, 0x16,
	0xB1, 0x03, 0xCC, 0xAB, 0x3E, 0x1F, 0xEA, 0x03, 0x8C, 0x90, 0xB1, 0x9A, 0x91, 0xC7, 0xAA, 0x62,
	0x9C, 0x66, 0xD7, 0x8C, 0xCB, 0xC6, 0x3B, 0x0F, 0xBA, 0xFE, 0xFB, 0x02, 0x40, 0x38, 0x70, 0xC7,
	0x8F, 0x89, 0x71, 0xDD, 0xF5, 0x8C, 0xCF, 0x7C, 0xDD, 0x83, 0x7E, 0x69, 0x4A, 0xE8, 0x0D, 0xAE,
	0xBF, 0x19, 0x6F, 0x08, 0xFE, 0x3D, 0xAA, 0xA6, 0xC0, 0xEF, 0xFA, 0xB9, 0xA5, 0xD0, 0x6C, 0x7B,
	0x64, 0x82, 0x0F, 0xD6, 0x58, 0xAC, 0x43, 0x6C, 0x70, 0x05, 0x9B, 0xA6, 0x0B, 0x75, 0x7F, 0xA7,
	0xF8, 0xF0, 0x58, 0x19, 0x6D, 0x84, 0xFD, 0x4A, 0xFD, 0xC8, 0x16, 0x78, 0xDB, 0x02, 0x40, 0x4C,
	0x50, 0x6F, 0xC9, 0x9E, 0x54, 0xCF, 0xD5, 0x01, 0xAA, 0x8E, 0xBB, 0x49, 0xB5, 0x8D, 0x41, 0x8B,
	0xF1, 0xE3, 0xFA, 0xF8, 0x3D, 0x32, 0xA0, 0x61, 0xA2, 0x88, 0x3C, 0x7E, 0x7E, 0x6F, 0xCA, 0x9C,
	0xBC, 0x2C, 0x8A, 0x68, 0xFB, 0x1B, 0x87, 0x54, 0x0E, 0xED, 0x58, 0x4B, 0x5D, 0x92, 0xEA, 0x52,
	0xBF, 0xF7, 0x89, 0x41, 0xE9, 0xC1, 0x54, 0x31, 0xEA, 0x92, 0x96, 0xF2, 0x43, 0x01, 0xBD
};

int security_sdk_setup_remove_key(void)
{
	artik_security_module *security = NULL;
	artik_security_handle handle = NULL;
	artik_error err = S_OK;
	char key_name[20] = { 0 };
	int ret, i, j, cnt = 0;
	unsigned int test_result = 0;
	unsigned int key_size[SEE_REMOVE_KEY_TC] = { 16, 24, 32, 128, 128};
	unsigned int key_type[SEE_REMOVE_KEY_TC] = { AES_128, AES_192, AES_256,
												 HMAC_ALGORITHM, HMAC_ALGORITHM
											   };
	unsigned char key[1280];

	fprintf(stderr, "------------------------------------------------------\n");
	fprintf(stderr, "  SECURITY SDK TESTCASE : setup/remove key\n");
	fprintf(stderr, "------------------------------------------------------\n");

	security = (artik_security_module *) artik_request_api_module("security");
	if (!security) {
		fprintf(stderr, "Security module is not available\n");
		return -1;
	}

	err = security->request(&handle);
	if (err != S_OK) {
		fprintf(stderr, "Failed to request security instance (err=%d)\n", err);
		err = -1;
		goto exit;
	}
	memset(key, 0xa5, sizeof(key));

	for (i = 0; i < SEE_REMOVE_KEY_TC; i++) {
		for (j = 0; j < 9; j++) {
			memset(key_name, 0, sizeof(key_name));
			sprintf(key_name, "%s/%X", SECURE_STORAGE_DEFAULT, j);

			ret = security->set_key(handle, key_type[i], key_name, key, key_size[i]);
			ret += security->remove_key(handle, key_type[i], key_name);

			see_selfprintf("[%d] ", cnt++);
			if (j == 8 && ret) {
				see_selfprintf(" success\n");
			} else if (ret) {
				test_result++;
				see_selfprintf(" fail : %d\n", ret);
			} else {
				see_selfprintf(" success\n");
			}
		}
	}

	for (i = 0; i < SEE_REMOVE_KEY_TC; i++) {
		for (j = 0; j < 5; j++) {
			memset(key_name, 0, sizeof(key_name));
			sprintf(key_name, "%s/%X", MEMORY_STORAGE, j);

			ret = security->set_key(handle, key_type[i], key_name, key, key_size[i]);
			ret += security->remove_key(handle, key_type[i], key_name);

			see_selfprintf("[%d] ", cnt++);
			if (j == 4 && ret) {
				see_selfprintf(" success\n");
			} else if (ret) {
				test_result++;
				see_selfprintf(" fail : %d\n", ret);
			} else {
				see_selfprintf(" success\n");
			}
		}
	}
exit:
	if (handle) {
		security->release(handle);
	}

	if (security) {
		artik_release_api_module(security);
	}

	return test_result;
}

