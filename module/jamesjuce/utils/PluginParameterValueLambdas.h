#pragma once


namespace ParameterLambdas
{

    static std::function<String (float)> dbValueToTextFunction = [](float value)
    {
        return Decibels::toString(value);
    };

    static std::function<String (float)> hzValueToTextFunction = [](float value)
    {
        if(value<1000.0f)
        {
            return String ((int)value) += " Hz";
        }
        else if (value<5000.0f)
        {
            return String (value/1000.0f,2) += " kHz";
        }
        else
        {
            return String (value/1000.0f,1) += " kHz";
        }
        
    };


    static std::function<String (float)> smallHzValueToTextFunction = [](float value)
    {
        if(value<1.0f)
        {
            return String (value,2) += " Hz";
        }
        else if (value<5.0f)
        {
            return String (value,1) += " Hz";
        }
        else
        {
            return String ((int)value) += " Hz";
        }
        
        
    };



    static std::function<String (float)> msValueToTextFunction = [](float value)
    {
        if(value<1000.0f)
            return String(value) + " ms";
        else
            return String(value/1000.0f,2) + " s";
        
    };

    static std::function<String (float)> secondsValueToTextFunction = [](float value)
    {
        if(value<1.0f)
            return String(value*1000.0f) + " ms";
        else
            return String(value,2) + " s";
        
    };




    static std::function<String (float)> fineSecondsValueToTextFunction = [](float value)
    {
        if(value<0.1f)
            return String(value*1000.0f,2) + " ms";
        if(value<1.0f)
            return String(value*1000.0f,1) + " ms";
        else
            return String(value,2) + " s";
        
    };





    static std::function<String (float)> percentValueToTextFunction = [](float value)
    {
        return String(value) + "%";
    };

    static std::function<String (float)> adimensionalValueToTextFunction = [](float value)
    {
        return String(value,2);
    };



    /*
     basic numerical text to value translation function.
     basic unit sistem is : seconds-hertz
     if "ms" or "kHz" is found in the text, a 10^3 mutiplication factor is used accordingly
     for other units the value is translated as is ( %, dB, samples....)
     
    */
    static std::function<float (String)> numericTextToValueFunction = [](const String& text) // text to value
    {
        float multiplier = 1.0f;
        
        if(text.containsIgnoreCase("ms")) multiplier = 0.001f;
        if(text.containsIgnoreCase("kHz")) multiplier = 1000.0f;
        
        String sanitizedText = text.retainCharacters("1234567890-.,");

        // humans tend to use commas for decimals
        return sanitizedText.replace(",", ".").getFloatValue() * multiplier;
    };
}







