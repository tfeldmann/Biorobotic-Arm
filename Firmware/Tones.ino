/**
 * Tones.ino
 */
#include "pitch.h"

const uint8_t SPEAKER_PIN = 8;

// Melody: "Ready"
const int tone_ready_m[] = {NOTE_C5, NOTE_G5};
const int tone_ready_d[] = {8,       8};

// Melody: "Collision"
const int tone_collision_m[] = {NOTE_C6, NOTE_C6};
const int tone_collision_d[] = {16,      16};


void tone_ready()
{
    tone_play(tone_ready_m, tone_ready_d, 2);
}

void tone_collision()
{
    tone_play(tone_collision_m, tone_collision_d, 2);
}

void tone_play(const int *melody, const int *durations, uint8_t length)
{
    for (int i = 0; i < length; i++)
    {
        // play note
        int note_duration = 1000 / durations[i];
        tone(SPEAKER_PIN, melody[i], note_duration);

        // short pause to distinguish the notes.
        // the note's duration + 30% seems to work well.
        int pause = note_duration * 1.3;
        delay(pause);
        noTone(SPEAKER_PIN);
    }
}
