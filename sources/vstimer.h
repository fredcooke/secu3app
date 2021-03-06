/* SECU-3  - An open source, free engine control unit
   Copyright (C) 2007 Alexey A. Shabelnikov. Ukraine, Gorlovka

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.

   contacts:
              http://secu-3.org
              email: shabelnikov@secu-3.org
*/

/** \file vstimer.h
 * Virtual system timers
 * (����������� ��������� �������).
 */

#ifndef _VSTIMER_H_
#define _VSTIMER_H_

#include "port/interrupt.h"
#include "port/intrinsic.h"
#include <stdint.h>

//�������������� ��� ���������� ����������� �������

//���� �������� ��������. 8-�� ��������� ������ ����� ����������� �������
//�� 2.56 ���. 16-�� ��������� ������ ����� ����������� ������� �� 655 ���.
typedef uint8_t   s_timer8_t;  //!< used by 8-bit timers
typedef uint16_t  s_timer16_t; //!< used by 16-bit timers

/**Update state of specified timer (���������� ��������� ���������� �������) */
#define s_timer_update(T)    { if ((T) > 0) (T)--; }

/**Initialization of state of specified timer. One tick = 10ms
 *(������������� ��������� ���������� �������. ���� ��� ������� ����� 10 ��). */
#define s_timer_set(T, V)    { (T) = (V); }

/**Checks whenever specified timer is completed (��������� �������� �� ��������� ������) */
#define s_timer_is_action(T) ((T)==0)

//����, �������� ������� ��� 16-�� ��������� ����������� ��������.
//��� ��� ��� ���� �������� ������������ �� ��������� ��� ������, ��
//���������� ��������� ����������.

/**Set specified timer for specified period */
#define s_timer16_set(T, V)  \
{                            \
 _DISABLE_INTERRUPT();       \
 (T) = (V);                  \
 _ENABLE_INTERRUPT();        \
}

/**Check specified timer for action */
INLINE
uint8_t s_timer16_is_action(s_timer16_t i_timer)
{
 uint8_t result;
 _BEGIN_ATOMIC_BLOCK();
 result = (i_timer == 0);
 _END_ATOMIC_BLOCK();
 return result;
}

/**Initialization of system timers */
void s_timer_init(void);

//////////////////////////////////////////////////////////////////
extern volatile s_timer8_t  send_packet_interval_counter;
extern volatile s_timer8_t  force_measure_timeout_counter;
extern volatile s_timer8_t  ce_control_time_counter;
extern volatile s_timer8_t  engine_rotation_timeout_counter;
extern volatile s_timer8_t  epxx_delay_time_counter;
extern volatile s_timer8_t  idle_period_time_counter;
extern volatile s_timer16_t save_param_timeout_counter;
//////////////////////////////////////////////////////////////////

#endif //_VSTIMER_H_
