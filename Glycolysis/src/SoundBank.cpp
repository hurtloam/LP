#include "../inc/SoundBank.h"


BSoundBank BSoundBank::SoundControl;

BSoundBank::BSoundBank () {
}

int
BSoundBank::OnLoad (const char * File) {
  Mix_Chunk* TempSound = NULL;

  if ((TempSound = Mix_LoadWAV(File)) == NULL)
  {
    SDL_LogError(SDL_LOG_CATEGORY_CUSTOM, "%s", Mix_GetError());
    SDL_LogError(SDL_LOG_CATEGORY_CUSTOM, "Could not load file: %s", File);
    return -1;
  }

  SoundList.push_back (TempSound);

  return (SoundList.size () - 1);
}

void
BSoundBank::OnCleanup () {
  for (unsigned int i = 0; i < SoundList.size (); i++)
  {
    Mix_FreeChunk (SoundList[i]);
  }

  SoundList.clear ();
}

void
BSoundBank::Play (int ID) {
  if (ID < 0 || ID >= (int) SoundList.size ())
    return;
  if (SoundList[ID] == NULL)
    return;

  Mix_PlayChannel(-1, SoundList[ID], 0);
}

void
BSoundBank::Repeat (int ID) {
  if (ID < 0 || ID >= (int) SoundList.size ())
    return;
  if (SoundList[ID] == NULL)
    return;

  Mix_PlayChannel(-1, SoundList[ID], -1);
}

void BSoundBank::FadeInChannel(int ID, int ms)
{
  if (ID < 0 || ID >= (int) SoundList.size())
    return;
  if (SoundList[ID] == NULL)
    return;

  Mix_FadeInChannel(-1, SoundList[ID], -1, ms);
}
void BSoundBank::Stop()
{

  Mix_HaltMusic();
}

