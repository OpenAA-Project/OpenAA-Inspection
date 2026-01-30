/*
 * Copyright (C) 2014
 * Author : Masatoshi Sasai ,MEGATRADE corporation
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#pragma once

// S
#define SEQ_REVIEW_S_MOTER_REQUIRE 200

#define SEQ_REVIEW_S_POSITION_X 201
#define SEQ_REVIEW_S_POSITION_Y 202
#define SEQ_REVIEW_S_POSITION_Z 203

#define SEQ_REVIEW_S_PULUS_PER_MM_X 204
#define SEQ_REVIEW_S_PULUS_PER_MM_Y 205
#define SEQ_REVIEW_S_PULUS_PER_MM_Z 206

// P
#define SEQ_REVIEW_P_MOTER_FLAG_X 100
#define SEQ_REVIEW_P_MOTER_FLAG_Y 101
#define SEQ_REVIEW_P_MOTER_FLAG_Z 102


namespace ReviewSequence
{

typedef enum {
	MotorRequireNone	=0,
	MotorRequireMoveX	=(1<<0),
	MotorRequireMoveY	=(1<<1),
	MotorRequireMoveZ	=(1<<2),
	MotorRequireMoveOrigin = (1<<3),
	MotorRequireMoveXY	=(MotorRequireMoveX | MotorRequireMoveY),
	MotorRequireMoveXZ	=(MotorRequireMoveX | MotorRequireMoveZ),
	MotorRequireMoveYZ	=(MotorRequireMoveY | MotorRequireMoveZ),
	MotorRequireMoveXYZ	=(MotorRequireMoveXY | MotorRequireMoveZ)
} SeqMotorRequire;

typedef unsigned int SeqMotorRequireFlags;
	
typedef enum {
	// �쓮�v���s��
	MotorIsLocked	=0,
	// ���v���\ 
	MotorIsIdle		=1
} SeqMotorState;

inline bool isIncludeFlags(SeqMotorRequireFlags ref, SeqMotorRequireFlags flags){
	return ((ref & flags)==flags);
};

}