#pragma once


//fefanto::PluginTempoSync test;
//DBG("At min value:  time = " << test.getTempoSyncLabel(0.0f) << " rate - " <<test.getTempoRateLabel(0.0f));
//DBG("At maxvalue:  time = " << test.getTempoSyncLabel(1.0f) << " rate - " <<test.getTempoRateLabel(1.0f));
//DBG("At 60 bpm (4/4): MINVAL  time = " << test.getTempoSyncTimeInSeconds(0.0f, 60.0, 4, 4) << " rate - " << test.getTempoSyncRateInHertz(0.0f, 60.0, 4, 4));
//DBG("At 60 bpm (4/4): MINVAL  time = " << test.getTempoSyncTimeInSeconds(1.0f, 60.0, 4, 4) << " rate - " << test.getTempoSyncRateInHertz(1.0f, 60.0, 4, 4));



class PluginTempoSync
{
public:
    static constexpr float TempoSyncSteps = 19.0f;
    enum SyncUnit{
        seconds = 0,
        hertz,
    };
    
public:
    PluginTempoSync();
    virtual ~PluginTempoSync();
    
public:
    
    static String getTempoSyncLabel(float normalizedValue0to1);
    static String getTempoRateLabel(float normalizedValue0to1);
    
    static double  getTempoSyncTimeInSeconds(float normalizedValue0to1,double bpm,int timeSigNumerator,int timeSigDenominator);
    static double  getTempoSyncRateInHertz(float normalizedValue0to1,double bpm,int timeSigNumerator,int timeSigDenominator);
    
    
    
    


/* 60 bpm , 4/4
    1 measure	0.25 Hz
    1/2• note	0.33 Hz
    1/2 note	0.50 Hz
    1/2T note	0.75 Hz
    1/4• note	0.67 Hz
    1/4 note	1.00 Hz
    1/4T note	1.50 Hz
    1/8• note	1.33 Hz
    1/8 note	2.00 Hz
    1/8T note	3.00 Hz
    1/16• note	2.67 Hz
    1/16 note	4.00 Hz
    1/16T note	6.00 Hz
    1/32• note	5.33 Hz
    1/32 note	8.00 Hz
    1/32T note	12.00 Hz
    1/64• note	10.67 Hz
    1/64 note	16.00 Hz
    1/64T note	24.00 Hz
 
 see : http://testtone.com/calculators/lfo-speed-calculator
*/
 
/* bpm & measure beats calculation
 
 Calculate seconds per beat by dividing 60 seconds per minute by beats per minute:
 seconds_per_beat = 60 / beats_per_minute
 
 Calculate seconds per measure by multiplying seconds per beat by beats per measure (in the time signature, the top number is the beats per measure, such as 3 in 3/4 time):
 seconds_per_measure = seconds_per_beat * beats_per_measure
 
 Calculate seconds per note by multiplying seconds per beat times the beat division (in the time signature, the bottom number is the beat division, such as 4 in 3/4 time), then divide by the note division you want (such as 2 for a 1/2 note):
 
 seconds_per_note = seconds_per_beat * (beat_division / note_division)
 Calculate dotted notes by multiplying by 1.5. Calculate triplet notes by multiplying by 0.67.
 seconds_per_dotted_note = 1.5 * seconds_per_note
 seconds_per_triplet_note = 0.67 * seconds_per_note
 Calculate the speed in Hertz by dividing 1 by seconds per note:
 hertz = 1 / seconds_per_note
 
 */

    
    
};

