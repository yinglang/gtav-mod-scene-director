/*
	THIS FILE IS A PART OF GTA V SCRIPT HOOK SDK
				http://dev-c.com
			(C) Alexander Blade 2015
*/

#pragma once

#include "..\..\inc\natives.h"
#include "..\..\inc\types.h"
#include "..\..\inc\enums.h"
#include "..\..\inc\main.h"
#include "Animation.h"
#include <string>

enum SCENE_MODE {
	SCENE_MODE_ACTIVE = 1,
	SCENE_MODE_SETUP = 0
};

enum VEHICLE_TYPE {
	VEHICLE_TYPE_CAR,
	VEHICLE_TYPE_HELI,
	VEHICLE_TYPE_PLANE,
	VEHICLE_TYPE_BOAT,
	VEHICLE_TYPE_SUB,
	VEHICLE_TYPE_BIKE
};

enum MENU_ITEM {
	MENU_ITEM_ACTOR_1 = 1,
	MENU_ITEM_ACTOR_2 = 2,
	MENU_ITEM_ACTOR_3 = 3,
	MENU_ITEM_ACTOR_4 = 4,
	MENU_ITEM_ACTOR_5 = 5,
	MENU_ITEM_ACTOR_6 = 6,
	MENU_ITEM_ACTOR_7 = 7,
	MENU_ITEM_ACTOR_8 = 8,
	MENU_ITEM_ACTOR_9 = 9,
	MENU_ITEM_SCENE_MODE = 110,
	MENU_ITEM_AUTOPILOT = 111,
	SUBMENU_ITEM_ESCORT = 112,
	SUBMENU_ITEM_CHASE = 113,
	MENU_ITEM_FIRING_SQUAD = 114,
	MENU_ITEM_ADD_TO_SLOT = 115,
	MENU_ITEM_ADD_CLONE_TO_SLOT = 116,
	MENU_ITEM_CLONE = 117,
	MENU_ITEM_CLONE_WITH_VEHICLE = 118,
	MENU_ITEM_POSSESS = 119,
	MENU_ITEM_WORLD = 120,
	MENU_ITEM_ANIMATION = 121,
	MENU_ITEM_BACK_TO_START = 122,
	MENU_ITEM_SAVE_LOAD = 123,
	MENU_ITEM_BIRDS_EYE_MODE = 124,
	MENU_ITEM_EXIT_BIRDS_EYE_MODE = 124,
	MENU_ITEM_SHOW_REC_MARKERS = 125,
	MENU_ITEM_EDIT_RECORDING = 126,
	SUBMENU_ITEM_RECORD_PLAYER = 140,
	SUBMENU_ITEM_REMOVE_FROM_SLOT = 141,
	SUBMENU_ITEM_SPOT_LIGHT = 142,
	SUBMENU_ITEM_SPOT_LIGHT_COLOR = 143,
	SUBMENU_ITEM_WALK = 144,
	SUBMENU_ITEM_RELATIONSHIP = 145,
	SUBMENU_ITEM_HEALTH = 146,
	SUBMENU_ITEM_VEHICLE_COSMETIC = 147,
	SUBMENU_ITEM_WALK_SPEED = 148,
	SUBMENU_ITEM_DRIVING_MODE = 149,
	SUBMENU_ITEM_TEST_RECORDING = 150,
	SUBMENU_ITEM_IS_PLAYING_RECORDING = 151,
	SUBMENU_ITEM_RECORD_PLAYER_WOTHERS = 152,
	SUBMENU_ITEM_DELETE_RECORDING = 153,
	SUBMENU_ITEM_RECORDING_DELAY = 154,
	SUBMENU_ITEM_COPY_REC_TO_OTHERS = 155,
	SUBMENU_ITEM_EDIT_NAME = 156,
	SUBMENU_ITEM_BLACKOUT = 160,
	SUBMENU_ITEM_TIMELAPSE = 161,
	SUBMENU_ITEM_WEATHER = 162,
	SUBMENU_ITEM_WIND = 163,
	SUBMENU_ITEM_RECORD_RELOAD = 164,
	SUBMENU_ITEM_ANIMATION_SINGLE = 170,
	SUBMENU_ITEM_ANIMATION_PREVIEW = 171,
	SUBMENU_ITEM_ANIMATION_FLAG = 172,
	SUBMENU_ITEM_ANIMATION_SEQUENCE = 173,
	SUBMENU_ITEM_ANIMATION_SYNC = 174,
	SUBMENU_ITEM_ANIMATION_SYNC_PREVIEW = 175,
	SUBMENU_ITEM_ACTOR_PROP_SELECT = 180,
	SUBMENU_ITEM_ACTOR_PROP_ADD = 181,
	SUBMENU_ITEM_SAVE_ACTORS = 190,
	SUBMENU_ITEM_LOAD_ACTORS = 191,
	SUBMENU_ITEM_ANIMATION_SEQUENCE_0 = 200,
	SUBMENU_ITEM_ANIMATION_SEQUENCE_1 = 201,
	SUBMENU_ITEM_ANIMATION_SEQUENCE_2 = 202,
	SUBMENU_ITEM_ANIMATION_SEQUENCE_3 = 203,
	SUBMENU_ITEM_ANIMATION_SEQUENCE_4 = 204,
	SUBMENU_ITEM_ANIMATION_SEQUENCE_5 = 205,
	SUBMENU_ITEM_ANIMATION_SEQUENCE_6 = 206,
	SUBMENU_ITEM_ANIMATION_SEQUENCE_7 = 207,
	SUBMENU_ITEM_ANIMATION_SEQUENCE_8 = 208,
	SUBMENU_ITEM_ANIMATION_SEQUENCE_9 = 209,
	SUBMENU_ITEM_ANIMATION_SEQUENCE_10 = 210,
	SUBMENU_ITEM_ANIMATION_SEQUENCE_11 = 211,
	SUBMENU_ITEM_ANIMATION_SEQUENCE_12 = 212,
	SUBMENU_ITEM_ANIMATION_SEQUENCE_13 = 213,
	SUBMENU_ITEM_ANIMATION_SEQUENCE_14 = 214,
	SUBMENU_ITEM_ANIMATION_SEQUENCE_15 = 215,
	SUBMENU_ITEM_ANIMATION_SEQUENCE_16 = 216,
	SUBMENU_ITEM_ANIMATION_SEQUENCE_17 = 217,
	SUBMENU_ITEM_ANIMATION_SEQUENCE_18 = 218,
	SUBMENU_ITEM_ANIMATION_SEQUENCE_19 = 219,
	SUBMENU_ITEM_ANIMATION_SEQUENCE_20 = 220,
	SUBMENU_ITEM_EDIT_LOCATION = 300,
	SUBMENU_ITEM_EDIT_ANIMATION = 301,
	SUBMENU_ITEM_EDIT_WALK_SPEED = 303,
	SUBMENU_ITEM_EDIT_WAIT = 304,
	SUBMENU_ITEM_NEXT_RECORDING = 305,
	SUBMENU_ITEM_PREV_RECORDING = 306,
	SUBMENU_ITEM_EDIT_VEH_SPEED = 307,
	SUBMENU_ITEM_EDIT_MIN_DIST_COMPL = 308,
	SUBMENU_ITEM_EDIT_TICKS_DELTA = 309,
	SUBMENU_ITEM_EDIT_ANIMATION_REC = 310,
	SUBMENU_ITEM_EDIT_NRATTEMPTS_BEFORE_SKIPPING = 311,
	SUBMENU_ITEM_EDIT_JUMP_OR_CLIMB = 312,
};

enum MARKER_TYPE {
	MARKER_TYPE_NORMAL = 0,
	MARKER_TYPE_HIGHLIGHTED = 1,
	MARKER_TYPE_SELECTED = 2
};

#define PI 3.14159265

void ScriptMain();

//TODO: Class-ify all the things!
void check_player_model();
void playback_recording_to_waypoint(Ped ped, Vector3 waypointCoord);
void log_to_file(std::string message, bool bAppend = true);
void set_status_text(std::string text);
void draw_spot_lights();
void action_teleport_to_start_locations();
void DRAW_TEXT(char* Text, float X, float Y, float S_X, float S_Y, int Font, bool Outline, bool Shadow, bool Center, bool RightJustify, int R, int G, int B, int A);
bool menu_up_key_pressed();
bool menu_down_key_pressed();
bool menu_left_key_pressed();
bool menu_right_key_pressed();
bool menu_select_key_pressed();
bool menu_delete_key_pressed();
void action_toggle_scene_mode();
void action_animation_sequence_play(AnimationSequence animSequence);