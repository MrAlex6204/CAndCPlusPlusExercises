#define SDL_MAIN_HANDLED
#include <stdio.h>
#include <stdbool.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "constants.h"


int game_is_running = FALSE;
SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
int last_frame_time = 0;
rect ball,paddle;
bool isPaused = false,started=false,loose=false,is_game_over=false;
position titlePos,subtitlePos;
int titleFontSz=28,subtitleFontSz=10,total_lives = 3,score=0;
SDL_Color titleColor = GREEN_COLOR;


int initialize_window(void){
	
	 

	if(SDL_Init(SDL_INIT_EVERYTHING)!=0 ){
		fprintf(stderr,"Error when initializing");
		return FALSE;
	}
	
	window = SDL_CreateWindow(
			NULL,
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			WINDOW_WIDTH,WINDOW_HEIGHT,
			SDL_WINDOW_BORDERLESS
		);
	
	if(!window){
		fprintf(stderr,"Error creating window");
		return FALSE;
	}
	
	renderer= SDL_CreateRenderer(window,-1,0);
	
	if(!renderer){
		fprintf(stderr,"Error creating renderer");
		return FALSE;
	}
	
	
	
	
	return TRUE;	
}

void setup(void){
	
	titlePos = CENTERED_POS;
	subtitlePos = (position){ CENTERED_X , CENTERED_Y + 25 };
	titleFontSz = 28;
	subtitleFontSz = 10;
	
	
	ball.x= (WINDOW_WIDTH/2) - (ball.width/2);
	ball.y=	(WINDOW_HEIGHT/2) - (ball.height/2);
	ball.width=15;
	ball.height=15;
	ball.vel.x=300;
	ball.vel.y=300;
	
	paddle.width=100;
	paddle.height=10;
	paddle.x = (WINDOW_WIDTH/2) - (paddle.width/2);
	paddle.y = WINDOW_HEIGHT - 70;
	paddle.vel.x = 0;
	paddle.vel.y = 0;
		
	
	
	
	
}

void process_input(void){
	SDL_Event event;
	SDL_PollEvent(&event);
	
	switch(event.type){
		
		case SDL_QUIT:
			//Exit game loop
			game_is_running = FALSE;
			
			break;
		case SDL_KEYDOWN://When key is down
		
			switch(event.key.keysym.sym){
				
				case SDLK_ESCAPE:
						printf("\n\nEnding game...\n\n");
						game_is_running=FALSE;					
					break;
					
				case SDLK_LEFT:
					
					paddle.vel.x = -400;
					
					break;
					
				case SDLK_RIGHT:
					
					paddle.vel.x= +400;
					
					break;
				case SDLK_SPACE:
					
					if(started){//Pause only when the game is stared
						
						isPaused = !isPaused;//Pause or Unpause		
						loose = false;
						
						if(is_game_over){
							
							score = 0;
							total_lives = 3;
							is_game_over=false;
							
						}
						
						
						
					}
					
					break;
				case SDLK_RETURN:
					
					started = true;
					
				break;
				
			}
			
			break;
		case SDL_KEYUP://When key is up
		
			switch(event.key.keysym.sym){
				
				case SDLK_LEFT:
					paddle.vel.x = 0;
					break;
				
				case SDLK_RIGHT:
					paddle.vel.x = 0;
					break;
				
			}
			
			break;
		
	}
	
}

void update(void){
	
	int time_to_wait = FRAME_TARGET_TIME - (SDL_GetTicks() - last_frame_time);
	
	
	if(time_to_wait > 0 && time_to_wait <= FRAME_TARGET_TIME){
		SDL_Delay(time_to_wait);//Delay per frame		
	}
	
	
	float delta_time = (SDL_GetTicks() - last_frame_time)/1000.0f;
	
	last_frame_time = SDL_GetTicks();
	
	if(started){
		titleColor = WHITE_COLOR;
		titleFontSz = 20;
		titlePos = (position){CENTERED_X,15};
	}
	
	if(started && !isPaused &&  !is_game_over){//Update position only when is not paused and not is game over
		
		//Update ball and paddle position
		ball.x	+=	ball.vel.x * delta_time;
		ball.y	+=	ball.vel.y * delta_time;
		
		paddle.x +=	paddle.vel.x * delta_time;
		paddle.y += paddle.vel.y * delta_time;
		
	}
	
	//Check for bal collision with the walls
	if(ball.x <= 0 || ball.x >= WINDOW_WIDTH-ball.width)
		ball.vel.x = -ball.vel.x;//==>Turn the ball to the other direction
		
	if(ball.y <= 0 || ball.y >= WINDOW_HEIGHT-ball.height)
		ball.vel.y = -ball.vel.y;//Turn the ball to the other direction
		
	//Check collision with the paddle
	if(ball.y+ball.height >= paddle.y && ball.x+ball.width >= paddle.x && ball.x <= paddle.x + paddle.width){
		ball.vel.y = -ball.vel.y;
		score += 10;//Increment score
		
	}
		
	//Prevent paddle from moving outside of the boundaries of the window
	if(paddle.x <= 0)
		paddle.x = 0;		
	if(paddle.x >= WINDOW_WIDTH - paddle.width)
		paddle.x = WINDOW_WIDTH - paddle.width;
		
	//Check if lost a live and if is game over
	if(ball.y+ball.height >= WINDOW_HEIGHT){
		ball.x = CENTERED_X - (ball.width * 0.5 );
		ball.y = CENTERED_Y - (ball.height * 0.5 );
		
		paddle.x = CENTERED_X - (paddle.width * 0.5);
				
		loose = true;		
		isPaused = true;
		total_lives--;
		
		if(total_lives <= 0){//Check if is game over when player lose all the lives
			is_game_over = true;					
		}
		
		
		
	}
	
	
	
	
	
}

void render(void){
	
	char* score_text[50];
	char* lives_text[50];
	
	SDL_SetRenderDrawColor(renderer,0,0,0,255);
	SDL_RenderClear(renderer);
	
	
	SDL_Rect ball_rect = toSDLRect(ball);
	SDL_Rect paddle_rect = toSDLRect(paddle);
	
	DrawText(renderer,"Pong Game",titleFontSz,titlePos,titleColor,true);
	
	DrawText(renderer,"Powered by @MrAlex6204",10,
	(position){
		CENTERED_X,WINDOW_HEIGHT-10
	}
	,WHITE_COLOR,true);
	
	if(is_game_over){//Game over
		
		sprintf(score_text,"Your score is %d",score);
		
		DrawText(renderer,"GAME OVER",28,(position){
			CENTERED_X,CENTERED_Y - 80
		},RED_COLOR,true);
		
		DrawText(renderer,score_text,subtitleFontSz,(position){
			CENTERED_X,CENTERED_Y - 50
		},WHITE_COLOR,true);
		
		DrawText(renderer,"[ Press spacebar start again ]",subtitleFontSz,(position){
			CENTERED_X,CENTERED_Y + 50
		},YELLOW_COLOR,true);
		
	}    
	
	if(loose && !is_game_over){//When loose a live
		
		DrawText(renderer,"Press spacebar to continue",subtitleFontSz,(position){
			CENTERED_X,CENTERED_Y + 30
		},RED_COLOR,true);
	}
	
	if(isPaused && started && !loose && !is_game_over){//When is paused
		DrawText(renderer,"Game paused",subtitleFontSz,subtitlePos,YELLOW_COLOR,true);
	}
	
	if(!started){//Is game is not started
		
		DrawText(renderer,"Press enter to start",subtitleFontSz,subtitlePos,WHITE_COLOR,true);
		
		
	}else{
		
		
		
		sprintf(score_text,"Score : %d",score);
		sprintf(lives_text,"Lives : %d",total_lives);
		
		//Score text
		DrawText(renderer,score_text,subtitleFontSz,(position){
			60,15
		},WHITE_COLOR,true);
		
		//Live left text
		DrawText(renderer,lives_text,subtitleFontSz,(position){
			WINDOW_WIDTH - 60,15
		},WHITE_COLOR,true);
		
		
		SDL_SetRenderDrawColor(renderer,255,255,255,255);
		SDL_RenderFillRect(renderer,&ball_rect);//==>Render ball
		SDL_RenderFillRect(renderer,&paddle_rect);//==>Rener paddle
		
	}
	
	SDL_RenderPresent(renderer);
	
}

void destroy_window(void){
	
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	
}

int main(int argc,char* argv[]) {
	
	game_is_running =  initialize_window();
	
	setup();
	
	while(game_is_running){
		
		process_input();
		update();
		render();
		
	}
	
	
	destroy_window();    
	
	return 0;
}



