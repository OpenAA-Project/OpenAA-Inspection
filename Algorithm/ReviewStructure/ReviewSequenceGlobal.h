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
	// 駆動要求不可
	MotorIsLocked	=0,
	// 動要求可能 
	MotorIsIdle		=1
} SeqMotorState;

inline bool isIncludeFlags(SeqMotorRequireFlags ref, SeqMotorRequireFlags flags){
	return ((ref & flags)==flags);
};

}
