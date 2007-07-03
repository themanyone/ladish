/* Names of standard MIDI events and controllers.
 * Copyright (C) 2007 Dave Robillard <http://drobilla.net>
 *
 * This library is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation; either version 2.1 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
 *
 */

#ifndef RAUL_MIDINAMES_H
#define RAUL_MIDINAMES_H

#include "midi_events.h"

namespace Raul {

/** \group midi
 */

static const uint8_t X_MIDI_CMD_NOTE_OFF = 0x80;

/** Pass this a symbol defined in midi_events.h (e.g. MIDI_CTL_PAN) to get the
 * short name of a MIDI event/controller according to General MIDI.
 */
static const char* midi_name(uint8_t status)
{
	switch (status) {
	
	case MIDI_CMD_NOTE_OFF:
		return "Note Off"; break;
	case MIDI_CMD_NOTE_ON:
		return "Note On"; break;
	case MIDI_CMD_NOTE_PRESSURE:
		return "Key Pressure"; break;
	case MIDI_CMD_CONTROL:
		return "Control Change"; break;
	case MIDI_CMD_PGM_CHANGE:
		return "Program Change"; break;
	case MIDI_CMD_CHANNEL_PRESSURE:
		return "Channel Pressure"; break;
	case MIDI_CMD_BENDER:
		return "Pitch Bender"; break;

	case MIDI_CMD_COMMON_SYSEX:
		return "Sysex (System Exclusive) Begin"; break;
	case MIDI_CMD_COMMON_MTC_QUARTER:
		return "MTC Quarter Frame"; break;
	case MIDI_CMD_COMMON_SONG_POS:
		return "Song Position"; break;
	case MIDI_CMD_COMMON_SONG_SELECT:
		return "Song Select"; break;
	case MIDI_CMD_COMMON_TUNE_REQUEST:
		return "Tune Request"; break;
	case MIDI_CMD_COMMON_SYSEX_END:
		return "End of Sysex"; break;
	case MIDI_CMD_COMMON_CLOCK:
		return "Clock"; break;
	case MIDI_CMD_COMMON_TICK:
		return "Tick"; break;
	case MIDI_CMD_COMMON_START:
		return "Start"; break;
	case MIDI_CMD_COMMON_CONTINUE:
		return "Continue"; break;
	case MIDI_CMD_COMMON_STOP:
		return "Stop"; break;
	case MIDI_CMD_COMMON_SENSING:
		return "Active Sensing"; break;
	case MIDI_CMD_COMMON_RESET:
		return "Reset"; break;

	case MIDI_CTL_MSB_BANK:
		return "Bank Selection"; break;
	case MIDI_CTL_MSB_MODWHEEL:
		return "Modulation"; break;
	case MIDI_CTL_MSB_BREATH:
		return "Breath"; break;
	case MIDI_CTL_MSB_FOOT:
		return "Foot"; break;
	case MIDI_CTL_MSB_PORTAMENTO_TIME:
		return "Portamento Time"; break;
	case MIDI_CTL_MSB_DATA_ENTRY:
		return "Data Entry"; break;
	case MIDI_CTL_MSB_MAIN_VOLUME:
		return "Main Volume"; break;
	case MIDI_CTL_MSB_BALANCE:
		return "Balance"; break;
	case MIDI_CTL_MSB_PAN:
		return "Panpot"; break;
	case MIDI_CTL_MSB_EXPRESSION:
		return "Expression"; break;
	case MIDI_CTL_MSB_EFFECT1:
		return "Effect1"; break;
	case MIDI_CTL_MSB_EFFECT2:
		return "Effect2"; break;
	case MIDI_CTL_MSB_GENERAL_PURPOSE1:
		return "General Purpose 1"; break;
	case MIDI_CTL_MSB_GENERAL_PURPOSE2:
		return "General Purpose 2"; break;
	case MIDI_CTL_MSB_GENERAL_PURPOSE3:
		return "General Purpose 3"; break;
	case MIDI_CTL_MSB_GENERAL_PURPOSE4:
		return "General Purpose 4"; break;
	case MIDI_CTL_LSB_BANK:
		return "Bank Selection"; break;
	case MIDI_CTL_LSB_MODWHEEL:
		return "Modulation"; break;
	case MIDI_CTL_LSB_BREATH:
		return "Breath"; break;
	case MIDI_CTL_LSB_FOOT:
		return "Foot"; break;
	case MIDI_CTL_LSB_PORTAMENTO_TIME:
		return "Portamento Time"; break;
	case MIDI_CTL_LSB_DATA_ENTRY:
		return "Data Entry"; break;
	case MIDI_CTL_LSB_MAIN_VOLUME:
		return "Main Volume"; break;
	case MIDI_CTL_LSB_BALANCE:
		return "Balance"; break;
	case MIDI_CTL_LSB_PAN:
		return "Panpot"; break;
	case MIDI_CTL_LSB_EXPRESSION:
		return "Expression"; break;
	case MIDI_CTL_LSB_EFFECT1:
		return "Effect1"; break;
	case MIDI_CTL_LSB_EFFECT2:
		return "Effect2"; break;
	case MIDI_CTL_LSB_GENERAL_PURPOSE1:
		return "General Purpose 1"; break;
	case MIDI_CTL_LSB_GENERAL_PURPOSE2:
		return "General Purpose 2"; break;
	case MIDI_CTL_LSB_GENERAL_PURPOSE3:
		return "General Purpose 3"; break;
	case MIDI_CTL_LSB_GENERAL_PURPOSE4:
		return "General Purpose 4"; break;
	case MIDI_CTL_SUSTAIN:
		return "Sustain Pedal"; break;
	case MIDI_CTL_PORTAMENTO:
		return "Portamento"; break;
	case MIDI_CTL_SOSTENUTO:
		return "Sostenuto"; break;
	case MIDI_CTL_SOFT_PEDAL:
		return "Soft Pedal"; break;
	case MIDI_CTL_LEGATO_FOOTSWITCH:
		return "Legato Foot Switch"; break;
	case MIDI_CTL_HOLD2:
		return "Hold2"; break;
	case MIDI_CTL_SC1_SOUND_VARIATION:
		return "SC1 Sound Variation"; break;
	case MIDI_CTL_SC2_TIMBRE:
		return "SC2 Timbre"; break;
	case MIDI_CTL_SC3_RELEASE_TIME:
		return "SC3 Release Time"; break;
	case MIDI_CTL_SC4_ATTACK_TIME:
		return "SC4 Attack Time"; break;
	case MIDI_CTL_SC5_BRIGHTNESS:
		return "SC5 Brightness"; break;
	case MIDI_CTL_SC6:
		return "SC6"; break;
	case MIDI_CTL_SC7:
		return "SC7"; break;
	case MIDI_CTL_SC8:
		return "SC8"; break;
	case MIDI_CTL_SC9:
		return "SC9"; break;
	case MIDI_CTL_SC10:
		return "SC10"; break;
	case MIDI_CTL_GENERAL_PURPOSE5:
		return "General Purpose 5"; break;
	case MIDI_CTL_GENERAL_PURPOSE6:
		return "General Purpose 6"; break;
	case MIDI_CTL_GENERAL_PURPOSE7:
		return "General Purpose 7"; break;
	case MIDI_CTL_GENERAL_PURPOSE8:
		return "General Purpose 8"; break;
	case MIDI_CTL_PORTAMENTO_CONTROL:
		return "Portamento Control"; break;
	case MIDI_CTL_E1_REVERB_DEPTH:
		return "E1 Reverb Depth"; break;
	case MIDI_CTL_E2_TREMOLO_DEPTH:
		return "E2 Tremolo Depth"; break;
	case MIDI_CTL_E3_CHORUS_DEPTH:
		return "E3 Chorus Depth"; break;
	case MIDI_CTL_E4_DETUNE_DEPTH:
		return "E4 Detune Depth"; break;
	case MIDI_CTL_E5_PHASER_DEPTH:
		return "E5 Phaser Depth"; break;
	case MIDI_CTL_DATA_INCREMENT:
		return "Data Increment"; break;
	case MIDI_CTL_DATA_DECREMENT:
		return "Data Decrement"; break;
	case MIDI_CTL_NONREG_PARM_NUM_LSB:
		return "Non-registered Parameter Number"; break;
	case MIDI_CTL_NONREG_PARM_NUM_MSB:
		return "Non-registered Narameter Number"; break;
	case MIDI_CTL_REGIST_PARM_NUM_LSB:
		return "Registered Parameter Number"; break;
	case MIDI_CTL_REGIST_PARM_NUM_MSB:
		return "Registered Parameter Number"; break;
	case MIDI_CTL_ALL_SOUNDS_OFF:
		return "All Sounds Off"; break;
	case MIDI_CTL_RESET_CONTROLLERS:
		return "Reset Controllers"; break;
	case MIDI_CTL_LOCAL_CONTROL_SWITCH:
		return "Local Control Switch"; break;
	case MIDI_CTL_ALL_NOTES_OFF:
		return "All Notes Off"; break;
	case MIDI_CTL_OMNI_OFF:
		return "Omni Off"; break;
	case MIDI_CTL_OMNI_ON:
		return "Omni On"; break;
	case MIDI_CTL_MONO1:
		return "Mono 1"; break;
	case MIDI_CTL_MONO2:
		return "Mono 2"; break;
	default:
		return "Unnamed"; break;
	}
}


} // namespace Raul

#endif /* RAUL_MIDINAMES_H */
