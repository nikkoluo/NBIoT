/*
 * Copyright (c) 2016, Sensirion AG
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 *
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 * * Neither the name of Sensirion AG nor the names of its
 *   contributors may be used to endorse or promote products derived from
 *   this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef SGPC1X_H
#define SGPC1X_H
#include "sensirion_common.h"

s16 sgp_probe(void);
s16 sgp_iaq_init(void);

u8 sgp_get_configured_address(void);
void sgp_get_serial_id(u64 *serial_id);

s16 sgp_get_iaq_baseline(u32 *baseline);
s16 sgp_set_iaq_baseline(u32 baseline);

s16 sgp_measure_iaq_blocking_read(u16 *tvoc_ppb, u16 *co2_eq_ppm);
s16 sgp_measure_iaq(void);
s16 sgp_read_iaq(u16 *tvoc_ppb, u16 *co2_eq_ppm);

s16 sgp_measure_tvoc_blocking_read(u16 *tvoc_ppb);
s16 sgp_measure_tvoc(void);
s16 sgp_read_tvoc(u16 *tvoc_ppb);

s16 sgp_measure_co2_eq_blocking_read(u16 *co2_eq_ppm);
s16 sgp_measure_co2_eq(void);
s16 sgp_read_co2_eq(u16 *co2_eq_ppm);

s16 sgp_measure_pixel_resistance_blocking_read(s64 *pixel_resistance1, s64 *pixel_resistance3);
s16 sgp_measure_pixel_resistance(void);
s16 sgp_read_pixel_resistance(s64 *pixel_resistance1, s64 *pixel_resistance3);

u16 sgp_measure_test(void);

#endif /* SGPC1X_H */

