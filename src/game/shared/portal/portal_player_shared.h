//========= Copyright � 1996-2005, Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
// $NoKeywords: $
//
//=============================================================================//
#ifndef PORTAL_PLAYER_SHARED_H
#define PORTAL_PLAYER_SHARED_H
#pragma once

#define PORTAL_PUSHAWAY_THINK_INTERVAL		(1.0f / 20.0f)
#include "studio.h"
#include "paint/paint_color_manager.h"
#include "cegclientwrapper.h"
#include "paint/paint_power_info.h"

const float STEEP_SLOPE = 0.7;
char const* const PORTAL_PREDICTED_CONTEXT = "Portal Predicted Powers";

//-----------------------------------------------------------------------------
// Purpose: Computes a local matrix for the player clamped to valid carry ranges
//-----------------------------------------------------------------------------
// when looking level, hold bottom of object 8 inches below eye level
#define PLAYER_HOLD_LEVEL_EYES	-8

// when looking down, hold bottom of object 0 inches from feet
#define PLAYER_HOLD_DOWN_FEET	2

// when looking up, hold bottom of object 24 inches above eye level
#define PLAYER_HOLD_UP_EYES		24

// use a +/-30 degree range for the entire range of motion of pitch
#define PLAYER_LOOK_PITCH_RANGE	30

// player can reach down 2ft below his feet (otherwise he'll hold the object above the bottom)
#define PLAYER_REACH_DOWN_DISTANCE	24


//=============================================================================
// Paint Power Choice
//=============================================================================
struct PaintPowerChoiceCriteria_t
{
	Vector vNormInputDir;
	Vector vNormVelocity;
	bool bInPortal;
};

struct PaintPowerChoiceResult_t
{
	const PaintPowerInfo_t* pPaintPower;
	float flInputCos;
	float flVelocityCos;
	bool bWasIgnored;

	inline void Initialize()
	{
		pPaintPower = NULL;
		flInputCos = 1.0f;
		flVelocityCos = 2.0f;
		bWasIgnored = false;
	}
};

typedef CUtlVectorFixed< PaintPowerChoiceResult_t, PAINT_POWER_TYPE_COUNT_PLUS_NO_POWER > PaintPowerChoiceResultArray;

void ExpandAABB(Vector& boxMin, Vector& boxMax, const Vector& sweepVector);

struct BrushContact
{
	Vector point;
	Vector normal;
	CBaseEntity* pBrushEntity;
	bool isOnThinSurface;

	void Initialize( const Vector& contactPt,
					 const Vector& normal,
					 CBaseEntity* pBrushEntity,
					 bool onThinSurface );
	void Initialize( const fltx4& contactPt,
		const fltx4& normal,
		CBaseEntity* pBrushEntity,
		bool onThinSurface );
};

typedef CUtlVector<BrushContact> ContactVector;
typedef CUtlVector<cplane_t> CollisionPlaneVector;
void ComputeAABBContactsWithBrushEntity( ContactVector& contacts, const Vector& boxOrigin, const Vector& boxMin, const Vector& boxMax, CBaseEntity* pBrushEntity, int contentsMask = CONTENTS_BRUSH_PAINT );
void ComputeAABBContactsWithBrushEntity( ContactVector& contacts, const cplane_t *pClipPlanes, int iClipPlaneCount, const Vector& boxOrigin, const Vector& boxMin, const Vector& boxMax, CBaseEntity* pBrushEntity, int contentsMask = CONTENTS_BRUSH_PAINT );


enum
{
	PLAYER_SOUNDS_CITIZEN = 0,
	PLAYER_SOUNDS_COMBINESOLDIER,
	PLAYER_SOUNDS_METROPOLICE,
	PLAYER_SOUNDS_MAX,
};

enum 
{
	CONCEPT_CHELL_IDLE,
	CONCEPT_CHELL_DEAD,
};

struct CachedPaintPowerChoiceResult
{
	Vector surfaceNormal;
	CBaseHandle surfaceEntity;
	bool wasValid;
	bool wasIgnored;

	inline void Initialize()
	{
		surfaceNormal = Vector(0, 0, 0);
		surfaceEntity = NULL;
		wasValid = false;
		wasIgnored = false;
	}
};

struct StringCompare_t
{
	StringCompare_t( char const* str ) : m_str( str ) {}

	char const* const m_str;

	inline bool operator()( char const* str ) const
	{
		return V_strcmp( m_str, str ) == 0;
	}
};

enum JumpButtonPress
{
	JUMP_ON_TOUCH = 0,
	PRESS_JUMP_TO_BOUNCE,
	HOLD_JUMP_TO_BOUNCE,
	TRAMPOLINE_BOUNCE
};

enum InAirState
{
	ON_GROUND,
	IN_AIR_JUMPED,
	IN_AIR_BOUNCED,
	IN_AIR_FELL
};

enum PaintSurfaceType
{
	FLOOR_SURFACE = 0,
	WALL_SURFACE,
	CEILING_SURFACE
};

enum StickCameraState
{
	STICK_CAMERA_SURFACE_TRANSITION = 0,
	STICK_CAMERA_ROLL_CORRECT,
	STICK_CAMERA_PORTAL,
	STICK_CAMERA_WALL_STICK_DEACTIVATE_TRANSITION,
	STICK_CAMERA_SWITCH_TO_ABS_UP_MODE,
	STICK_CAMERA_ABS_UP_MODE,
	STICK_CAMERA_SWITCH_TO_LOCAL_UP,
	STICK_CAMERA_SWITCH_TO_LOCAL_UP_LOOKING_UP,
	STICK_CAMERA_LOCAL_UP_LOOKING_UP,
	STICK_CAMERA_UPRIGHT
};

enum StickCameraCorrectionMethod
{
	QUATERNION_CORRECT = 0,
	ROTATE_UP,
	SNAP_UP,
	DO_NOTHING
};

extern const char *g_pszChellConcepts[];
int GetChellConceptIndexFromString( const char *pszConcept );

#if defined( CLIENT_DLL )
#define CPortal_Player C_Portal_Player
#endif


#endif //PORTAL_PLAYER_SHARED_h
