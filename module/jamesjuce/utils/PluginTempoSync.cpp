

PluginTempoSync::PluginTempoSync()
{
}

PluginTempoSync::~PluginTempoSync()
{
    
}


String PluginTempoSync::getTempoSyncLabel(float normalizedValue0to1)
{
    jassert(normalizedValue0to1 >= 0.0f  && normalizedValue0to1 <= 1.0f);
    
    int selector = (int)(normalizedValue0to1 * PluginTempoSync::TempoSyncSteps);
    String label = String();
    
    switch (selector)
    {
        case 0: label = "1/64T"; break;
        case 1: label = "1/64"; break;
        case 2: label = "1/64."; break;
        case 3: label = "1/32T"; break;
        case 4: label = "1/32"; break;
        case 5: label = "1/32."; break;
        case 6: label = "1/16T"; break;
        case 7: label = "1/16"; break;
        case 8: label = "1/16."; break;
        case 9: label = "1/8T"; break;
        case 10:label = "1/8"; break;
        case 11:label = "1/8."; break;
        case 12:label = "1/4T"; break;
        case 13:label = "1/4"; break;
        case 14:label = "1/4."; break;
        case 15:label = "1/2T"; break;
        case 16:label = "1/2"; break;
        case 17:label = "1/2."; break;
        case 18:label = "1/1"; break;
        case 19:label = "1/1"; break; // hack to compensate the 0 case for the rate label
    }
    
    return label;
    
    
}


String PluginTempoSync::getTempoRateLabel(float normalizedValue0to1)
{
    jassert(normalizedValue0to1 >= 0.0f  && normalizedValue0to1 <= 1.0f);
    
    if(normalizedValue0to1==0.0f) return "OFF"; // single point where even in tempo sync, rate is 0

    float inverseValue = 1.0f - normalizedValue0to1;  //
    return getTempoSyncLabel(inverseValue);
}




double PluginTempoSync::getTempoSyncTimeInSeconds(float normalizedValue0to1,double bpm,int timeSigNumerator,int timeSigDenominator)
{
    jassert(normalizedValue0to1 >= 0.0f  && normalizedValue0to1 <= 1.0f);
    jassert(bpm>0.0);
    if(bpm<20.0)bpm = 20.0; // better than a crash in release mode
    
    double secondsPerBeat = (60.0/bpm);
    //double secondsPerMeasure = secondsPerBeat*timeSigNumerator; // numerator not taken into account....
    double noMultiplier = 1.0;
    double dotMultiplier = 1.5;
    double tripletMultiplier = 0.67;
    
    int selector = (int)(normalizedValue0to1 * PluginTempoSync::TempoSyncSteps);
    double time = 0.0;
    
    
    switch (selector)
    {
        case 0: time = secondsPerBeat * (timeSigDenominator / 64.0) * tripletMultiplier; break; // "1/64T"
        case 1: time = secondsPerBeat * (timeSigDenominator / 64.0) * noMultiplier; break;      // "1/64"
        case 2: time = secondsPerBeat * (timeSigDenominator / 64.0) * dotMultiplier; break;     // "1/64."
        case 3: time = secondsPerBeat * (timeSigDenominator / 32.0) * tripletMultiplier; break; //= "1/32T"
        case 4: time = secondsPerBeat * (timeSigDenominator / 32.0) * noMultiplier; break;      // "1/32"
        case 5: time = secondsPerBeat * (timeSigDenominator / 32.0) * dotMultiplier; break;     // "1/32."
        case 6: time = secondsPerBeat * (timeSigDenominator / 16.0) * tripletMultiplier; break; // "1/16T"
        case 7: time = secondsPerBeat * (timeSigDenominator / 16.0) * noMultiplier; break;      // "1/16"
        case 8: time = secondsPerBeat * (timeSigDenominator / 16.0) * dotMultiplier; break;     // "1/16."
        case 9: time = secondsPerBeat * (timeSigDenominator / 8.0)  * tripletMultiplier; break; // "1/8T"
        case 10:time = secondsPerBeat * (timeSigDenominator / 8.0)  * noMultiplier; break;      // "1/8"
        case 11:time = secondsPerBeat * (timeSigDenominator / 8.0)  * dotMultiplier; break;     // "1/8."
        case 12:time = secondsPerBeat * (timeSigDenominator / 4.0)  * tripletMultiplier; break; // "1/4T"
        case 13:time = secondsPerBeat * (timeSigDenominator / 4.0)  * noMultiplier; break;      // "1/4"
        case 14:time = secondsPerBeat * (timeSigDenominator / 4.0)  * dotMultiplier; break;     // "1/4."
        case 15:time = secondsPerBeat * (timeSigDenominator / 2.0)  * tripletMultiplier; break; // "1/2T"
        case 16:time = secondsPerBeat * (timeSigDenominator / 2.0)  * noMultiplier; break;      // "1/2"
        case 17:time = secondsPerBeat * (timeSigDenominator / 2.0)  * dotMultiplier; break;     // "1/2."
        case 18:time = secondsPerBeat * (timeSigDenominator / 1.0)  * noMultiplier; break;      // "1/1"; break;
    }
    
    return time;
    
    
}



double PluginTempoSync::getTempoSyncRateInHertz(float normalizedValue0to1,double bpm,int timeSigNumerator,int timeSigDenominator)
{
    
    
    jassert(normalizedValue0to1>=0.0f  && normalizedValue0to1<=1.0f);
    
    if(normalizedValue0to1==0.0f) return 0.0f; // single point where even in tempo sync, rate is 0
    
    
    float incomingValue = 1.0f - normalizedValue0to1;  //
    double time = getTempoSyncTimeInSeconds(incomingValue,bpm,timeSigNumerator,timeSigDenominator);
    jassert(time>0.0f);
    return 1.0f/time;
}









