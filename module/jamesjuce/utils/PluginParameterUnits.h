#pragma once


enum PluginParameterUnits{
    adimensional = 0,
    percent,
    seconds,
    milliseconds,
    samples,
    hertz,
    radians,
    dB,
};


inline String PluginParameterUnitsToString(PluginParameterUnits units, bool prependSpace = false){
    String prefix = prependSpace ? String(" "):String();
    switch (units) {
        case adimensional:
            return String(prefix);
            break;
        case percent:
            return String(prefix+"%");
            break;
        case seconds:
            return String(prefix+"s.");
            break;
        case milliseconds:
            return String(prefix+"ms.");
            break;
        case samples:
            return String(prefix+"smp.");
            break;
        case hertz:
            return String(prefix+"Hz");
            break;
        case radians:
            return String(prefix+"rad.");
            break;
        case dB:
            return String(prefix+"dB");
            break;
        default:
            return String(prefix+"?units?");
            jassertfalse;
            break;
    }
}




