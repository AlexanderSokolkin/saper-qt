#ifndef HELPER_H
#define HELPER_H

#define BEGINNER_WIDTH 10
#define BEGINNER_HEIGHT 10
#define BEGINNER_BOMB_COUNT 10

#define AMATEUR_WIDTH 15
#define AMATEUR_HEIGHT 20
#define AMATEUR_BOMB_COUNT 30

#define PROFESSIONAL_WIDTH 30
#define PROFESSIONAL_HEIGHT 20
#define PROFESSIONAL_BOMB_COUNT 100

#define BUTTONS_SIZE 30

#define BEGINNER_FIELD_WIDTH		BEGINNER_WIDTH		*	BUTTONS_SIZE + 44
#define BEGINNER_FIELD_HEIGHT		BEGINNER_HEIGHT		*	BUTTONS_SIZE + 117
#define AMATEUR_FIELD_WIDTH			AMATEUR_WIDTH		*	BUTTONS_SIZE + 44
#define AMATEUR_FIELD_HEIGHT		AMATEUR_HEIGHT		*	BUTTONS_SIZE + 117
#define PROFESSIONAL_FIELD_WIDTH	PROFESSIONAL_WIDTH	*	BUTTONS_SIZE + 44
#define PROFESSIONAL_FIELD_HEIGHT	PROFESSIONAL_HEIGHT *	BUTTONS_SIZE + 117

#define USER_MODE_FIELD_WIDTH(cells) cells * BUTTONS_SIZE + 44
#define USER_MODE_FIELD_HEIGHT(cells) cells * BUTTONS_SIZE + 117

#endif // HELPER_H
