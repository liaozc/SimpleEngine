#ifndef DRAW_VERT_H
#define DRAW_VERT_H

class seDrawVert {
public:
	seVec3			xyz;
	seVec4			color;	//TODO: how to make it byte type each component as showed below
	seVec3			normal;
/*
	seVec2			st;
	seVec3			normal;
	seVec3			tangents[2];
	byte			color[4];
*/
};


#endif
