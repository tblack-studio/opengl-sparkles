#pragma once
// https://devcry.heiho.net/html/2017/20170930-opengl-spritesheet.html

struct TexSprite
{
		float x, y, w, h;
		float tx, ty, tw, th;

		void setTexInfo(float imgW, float imgH) {
				auto px = 1.0f / imgW;			// one pixel in texture space
				auto half_px = px * 0.5f;		// 1 / 2 pixel in texture space
				auto py = 1.0f / imgH;			// one pixel height in texture space
				auto half_py = py * 0.5f;		// 1 / 2 pixel in texture space

				// make texture coords for sprite(x, y, w, h)
				tx = x * px - half_px;
				ty = y * py - half_py;
				tw = w * px + px;
				th = h * py + py;
		}
};

