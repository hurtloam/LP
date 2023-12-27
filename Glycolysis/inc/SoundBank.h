#ifndef _CSOUNDBANK_H_
    #define _CSOUNDBANK_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <vector>


class BSoundBank {
public:
  static BSoundBank SoundControl;

  std::vector<Mix_Chunk*> SoundList;

public:
  BSoundBank ();

  int
  OnLoad (const char* File);

  void
  OnCleanup ();

public:
  void
  Play (int ID);

  void FadeInChannel(int ID, int ms);


  void
  Repeat (int ID);

  void Stop();
};


#endif
