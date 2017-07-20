#pragma once



#define DECLARE_PARAMETER_CONSTANTS(paramKey,paramID,paramName,paramLabel,lowestValue,highestValue,defaultValue,units,step,skew,skewsimmetric) \
static String  paramKey##ID = paramID; \
static String  paramKey##Name = paramName; \
static String  paramKey##Label = paramLabel; \
static constexpr float  paramKey##LowestValue  = lowestValue; \
static constexpr float  paramKey##HighestValue = highestValue; \
static constexpr float  paramKey##DefaultValue = defaultValue; \
static constexpr float  paramKey##Step                   = step; \
static constexpr float  paramKey##Skew                   = skew; \
static constexpr bool   paramKey##SkewSimmetric          = skewsimmetric; \
static NormalisableRange<float> paramKey##Range = NormalisableRange<float>( \
                                                                        paramKey##LowestValue, \
                                                                        paramKey##HighestValue, \
                                                                        paramKey##Step, \
                                                                        paramKey##Skew, \
                                                                        paramKey##SkewSimmetric \
                                                                        );

#define PARAMETER_ID_VARIABLE(paramKey) paramKey##ID
#define PARAMETER_ID_STRING(paramKey) "paramKey##ID"
#define PARAMETER_DEFAULT_VARIABLE(paramKey) paramKey##DefaultValue

#define VTS_ADD_PARAMS(paramKey,valuetotextlambda,texttovaluelambda)  \
paramKey##ID,   \
paramKey##Name, \
String(""),   \
paramKey##Range, \
paramKey##DefaultValue, \
valuetotextlambda, \
texttovaluelambda

#define STORYBOARD_ADD_PARAMS(paramKey)    \
paramKey##ID,    \
paramKey##Name,  \
paramKey##Label    \


// TBD Units
//static constexpr units  paramKey##Units        = units;


