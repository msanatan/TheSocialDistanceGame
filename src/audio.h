#ifndef SONG_H
#define SONG_H

#define Song const uint16_t PROGMEM

Song player_hit_sfx[] = {
    //"Track channel 0"
    0x9D, 24,  // FX: SET TEMPO: tempo = 24
    0x40, 48,  // FX: SET VOLUME: volume = 4
    TONES_END};

#endif
