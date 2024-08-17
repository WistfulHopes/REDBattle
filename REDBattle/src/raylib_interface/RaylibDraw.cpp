#include "RaylibDraw.h"

#include "rlgl.h"

void DrawTexturePlane(Texture2D texture, Vector3 pos, Vector2 size, Vector2 texcoords[4], Color color)
{
    rlSetTexture(texture.id);
    
    rlPushMatrix();
    rlTranslatef(pos.x, pos.y, pos.z);
    rlScalef(size.x, size.y, 1);

    rlBegin(RL_QUADS);
    rlColor4ub(color.r, color.g, color.b, color.a);
    rlNormal3f(0.0f, 1.0f, 0.0f);

    rlTexCoord2f(texcoords[0].x, texcoords[0].y);
    rlVertex3f(-0.5f, -0.5f, 0.f);
    rlTexCoord2f(texcoords[1].x, texcoords[1].y);
    rlVertex3f(-0.5f, 0.5f, 0.0f);
    rlTexCoord2f(texcoords[2].x, texcoords[2].y);
    rlVertex3f(0.5f, 0.5f, 0.0f);
    rlTexCoord2f(texcoords[3].x, texcoords[3].y);
    rlVertex3f(0.5f, -0.5f, 0.0f);
    rlEnd();
    rlSetTexture(0);
    rlPopMatrix();
}
