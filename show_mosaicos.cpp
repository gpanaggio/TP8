#include "show_mosaicos.h"


bool show_mosaicos(vector<mosaico>& vecM)
{
	ALLEGRO_DISPLAY * display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	bool exit = false;
	unsigned int i = 0;
	bool redraw = true;
	unsigned int temp;


	event_queue = al_create_event_queue();
	if (!event_queue) {
		fprintf(stderr, "failed to create event_queue!\n");
		return 1;
	}

	display = al_create_display(SCREEN_W, SCREEN_H);
	if (!display) {
		al_shutdown_primitives_addon();
		fprintf(stderr, "failed to create display!\n");
		return 1;
	}

	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_keyboard_event_source());

	while (!exit)
	{
		ALLEGRO_EVENT ev;

		if (al_get_next_event(event_queue, &ev))
		{
			if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
			{
				switch (ev.keyboard.keycode)
				{
				case ALLEGRO_KEY_1:
					vecM[i].select();
					redraw = true;
					break;
				case ALLEGRO_KEY_2:
					if (i + 1 < vecM.size())
						vecM[i + 1].select();
					redraw = true;
					break;
				case ALLEGRO_KEY_3:
					if (i + 2 < vecM.size())
						vecM[i + 2].select();
					redraw = true;
					break;
				case ALLEGRO_KEY_4:
					if (i + 3 < vecM.size())
						vecM[i + 3].select();
					redraw = true;
					break;
				case ALLEGRO_KEY_5:
					if (i + 4 < vecM.size())
						vecM[i + 4].select();
					redraw = true;
					break;
				case ALLEGRO_KEY_6:
					if (i + 5 < vecM.size())
						vecM[i + 5].select();
					redraw = true;
					break;
				case ALLEGRO_KEY_7:
					if (i + 6 < vecM.size())
						vecM[i + 6].select();
					redraw = true;
					break;
				case ALLEGRO_KEY_8:
					if (i + 7 < vecM.size())
						vecM[i + 7].select();
					redraw = true;
					break;
				case ALLEGRO_KEY_9:
					if (i + 8 < vecM.size())
						vecM[i + 8].select();
					redraw = true;
					break;
				case ALLEGRO_KEY_A:
					for (unsigned int temp = i; temp < vecM.size() && temp < i + 9; temp++)
						vecM[temp].selected = true;
					redraw = true;
					break;
				case ALLEGRO_KEY_N:
					for (unsigned int temp = i; temp < vecM.size() && temp < i + 9; temp++)
						vecM[temp].selected = false;
					redraw = true;
					break;
				case ALLEGRO_KEY_LEFT:
					if (i >= 9)
						i -= 9;
					redraw = true;
					break;
				case ALLEGRO_KEY_RIGHT:
					if (vecM.size() > (i + 9))
						i += 9;
					redraw = true;
					break;
				case ALLEGRO_KEY_ENTER:
					exit = true;
					break;
				default:
					break;
				}
			}
			else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
				exit = true;
		}


		if (redraw && al_is_event_queue_empty(event_queue))
		{
			redraw = false;
			al_clear_to_color(al_map_rgb(0, 0, 0));

			temp = i + 9;
			for (i; (i < vecM.size()) && (i < temp); i++)
			{
				switch (i % 9)
				{
				case 0:
					al_draw_scaled_bitmap(vecM[i].mosaicoBitmap, 0, 0, al_get_bitmap_width(vecM[i].mosaicoBitmap), al_get_bitmap_height(vecM[i].mosaicoBitmap), FIRST_COLUMN, FIRST_ROW, MOSAICO_SIZE, MOSAICO_SIZE, 0);
					if (vecM[i].selected)
						al_draw_rectangle(FIRST_COLUMN - 5, FIRST_ROW - 5, FIRST_COLUMN + MOSAICO_SIZE + 5, FIRST_ROW + MOSAICO_SIZE + 5, al_map_rgb(0, 255, 0), 10.0);
					else
						al_draw_rectangle(FIRST_COLUMN - 5, FIRST_ROW - 5, FIRST_COLUMN + MOSAICO_SIZE + 5, FIRST_ROW + MOSAICO_SIZE + 5, al_map_rgb(255, 0, 0), 10.0);
					break;

				case 1:
					al_draw_scaled_bitmap(vecM[i].mosaicoBitmap, 0, 0, al_get_bitmap_width(vecM[i].mosaicoBitmap), al_get_bitmap_height(vecM[i].mosaicoBitmap), SECOND_COLUMN, FIRST_ROW, MOSAICO_SIZE, MOSAICO_SIZE, 0);
					if (vecM[i].selected)
						al_draw_rectangle(SECOND_COLUMN - 5, FIRST_ROW - 5, SECOND_COLUMN + MOSAICO_SIZE + 5, FIRST_ROW + MOSAICO_SIZE + 5, al_map_rgb(0, 255, 0), 10.0);
					else
						al_draw_rectangle(SECOND_COLUMN - 5, FIRST_ROW - 5, SECOND_COLUMN + MOSAICO_SIZE + 5, FIRST_ROW + MOSAICO_SIZE + 5, al_map_rgb(255, 0, 0), 10.0);
					break;
				case 2:

					al_draw_scaled_bitmap(vecM[i].mosaicoBitmap, 0, 0, al_get_bitmap_width(vecM[i].mosaicoBitmap), al_get_bitmap_height(vecM[i].mosaicoBitmap), THIRD_COLUMN, FIRST_ROW, MOSAICO_SIZE, MOSAICO_SIZE, 0);
					if (vecM[i].selected)
						al_draw_rectangle(THIRD_COLUMN - 5, FIRST_ROW - 5, THIRD_COLUMN + MOSAICO_SIZE + 5, FIRST_ROW + MOSAICO_SIZE + 5, al_map_rgb(0, 255, 0), 10.0);
					else
						al_draw_rectangle(THIRD_COLUMN - 5, FIRST_ROW - 5, THIRD_COLUMN + MOSAICO_SIZE + 5, FIRST_ROW + MOSAICO_SIZE + 5, al_map_rgb(255, 0, 0), 10.0);
					break;
				case 3:
					al_draw_scaled_bitmap(vecM[i].mosaicoBitmap, 0, 0, al_get_bitmap_width(vecM[i].mosaicoBitmap), al_get_bitmap_height(vecM[i].mosaicoBitmap), FIRST_COLUMN, SECOND_ROW, MOSAICO_SIZE, MOSAICO_SIZE, 0);
					if (vecM[i].selected)
						al_draw_rectangle(FIRST_COLUMN - 5, SECOND_ROW - 5, FIRST_COLUMN + MOSAICO_SIZE + 5, SECOND_ROW + MOSAICO_SIZE + 5, al_map_rgb(0, 255, 0), 10.0);
					else
						al_draw_rectangle(FIRST_COLUMN - 5, SECOND_ROW - 5, FIRST_COLUMN + MOSAICO_SIZE + 5, SECOND_ROW + MOSAICO_SIZE + 5, al_map_rgb(255, 0, 0), 10.0);
					break;
				case 4:
					al_draw_scaled_bitmap(vecM[i].mosaicoBitmap, 0, 0, al_get_bitmap_width(vecM[i].mosaicoBitmap), al_get_bitmap_height(vecM[i].mosaicoBitmap), SECOND_COLUMN, SECOND_ROW, MOSAICO_SIZE, MOSAICO_SIZE, 0);
					if (vecM[i].selected)
						al_draw_rectangle(SECOND_COLUMN - 5, SECOND_ROW - 5, SECOND_COLUMN + MOSAICO_SIZE + 5, SECOND_ROW + MOSAICO_SIZE + 5, al_map_rgb(0, 255, 0), 10.0);
					else
						al_draw_rectangle(SECOND_COLUMN - 5, SECOND_ROW - 5, SECOND_COLUMN + MOSAICO_SIZE + 5, SECOND_ROW + MOSAICO_SIZE + 5, al_map_rgb(255, 0, 0), 10.0);
					break;
				case 5:
					al_draw_scaled_bitmap(vecM[i].mosaicoBitmap, 0, 0, al_get_bitmap_width(vecM[i].mosaicoBitmap), al_get_bitmap_height(vecM[i].mosaicoBitmap), THIRD_COLUMN, SECOND_ROW, MOSAICO_SIZE, MOSAICO_SIZE, 0);
					if (vecM[i].selected)
						al_draw_rectangle(THIRD_COLUMN - 5, SECOND_ROW - 5, THIRD_COLUMN + MOSAICO_SIZE + 5, SECOND_ROW + MOSAICO_SIZE + 5, al_map_rgb(0, 255, 0), 10.0);
					else
						al_draw_rectangle(THIRD_COLUMN - 5, SECOND_ROW - 5, THIRD_COLUMN + MOSAICO_SIZE + 5, SECOND_ROW + MOSAICO_SIZE + 5, al_map_rgb(255, 0, 0), 10.0);
					break;
				case 6:
					al_draw_scaled_bitmap(vecM[i].mosaicoBitmap, 0, 0, al_get_bitmap_width(vecM[i].mosaicoBitmap), al_get_bitmap_height(vecM[i].mosaicoBitmap), FIRST_COLUMN, THIRD_ROW, MOSAICO_SIZE, MOSAICO_SIZE, 0);
					if (vecM[i].selected)
						al_draw_rectangle(FIRST_COLUMN - 5, THIRD_ROW - 5, FIRST_COLUMN + MOSAICO_SIZE + 5, THIRD_ROW + MOSAICO_SIZE + 5, al_map_rgb(0, 255, 0), 10.0);
					else
						al_draw_rectangle(FIRST_COLUMN - 5, THIRD_ROW - 5, FIRST_COLUMN + MOSAICO_SIZE + 5, THIRD_ROW + MOSAICO_SIZE + 5, al_map_rgb(255, 0, 0), 10.0);
					break;
				case 7:
					al_draw_scaled_bitmap(vecM[i].mosaicoBitmap, 0, 0, al_get_bitmap_width(vecM[i].mosaicoBitmap), al_get_bitmap_height(vecM[i].mosaicoBitmap), SECOND_COLUMN, THIRD_ROW, MOSAICO_SIZE, MOSAICO_SIZE, 0);
					if (vecM[i].selected)
						al_draw_rectangle(SECOND_COLUMN - 5, THIRD_ROW - 5, SECOND_COLUMN + MOSAICO_SIZE + 5, THIRD_ROW + MOSAICO_SIZE + 5, al_map_rgb(0, 255, 0), 10.0);
					else
						al_draw_rectangle(SECOND_COLUMN - 5, THIRD_ROW - 5, SECOND_COLUMN + MOSAICO_SIZE + 5, THIRD_ROW + MOSAICO_SIZE + 5, al_map_rgb(255, 0, 0), 10.0);
					break;
				case 8:
					al_draw_scaled_bitmap(vecM[i].mosaicoBitmap, 0, 0, al_get_bitmap_width(vecM[i].mosaicoBitmap), al_get_bitmap_height(vecM[i].mosaicoBitmap), THIRD_COLUMN, THIRD_ROW, MOSAICO_SIZE, MOSAICO_SIZE, 0);
					if (vecM[i].selected)
						al_draw_rectangle(THIRD_COLUMN - 5, THIRD_ROW - 5, THIRD_COLUMN + MOSAICO_SIZE + 5, THIRD_ROW + MOSAICO_SIZE + 5, al_map_rgb(0, 255, 0), 10.0);
					else
						al_draw_rectangle(THIRD_COLUMN - 5, THIRD_ROW - 5, THIRD_COLUMN + MOSAICO_SIZE + 5, THIRD_ROW + MOSAICO_SIZE + 5, al_map_rgb(255, 0, 0), 10.0);
					break;
				default:
					break;
				}
			}
			i = temp - 9;
			al_flip_display();
		}
	}
	al_destroy_display(display);

	return 0;
}
