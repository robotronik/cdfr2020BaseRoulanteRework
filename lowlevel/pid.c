#include "include/pid.h"

void PID_SetParameters(PID_Data* PID, TYPE_ASSERVISSEMENT_PID_PARAM InP, TYPE_ASSERVISSEMENT_PID_PARAM InI, TYPE_ASSERVISSEMENT_PID_PARAM InD, TYPE_ASSERVISSEMENT_PID_INTEGRAL InAbsIMax)
{
    PID->P = InP;
    PID->I = InI;
    PID->D = InD;
    PID->AbsIMax = InAbsIMax;
    if (PID->Integration > InAbsIMax)
    {
        PID->Integration = InAbsIMax;
    }
    else if (PID->Integration < -InAbsIMax)
    {
        PID->Integration = -InAbsIMax;
    }
}

void PID_SetTarget(PID_Data* PID, TYPE_ASSERVISSEMENT_PID_POS NewTarget)
{
    PID->Target = NewTarget;
}

void PID_Reset(PID_Data* PID, TYPE_ASSERVISSEMENT_PID_TIME Time, TYPE_ASSERVISSEMENT_PID_INTEGRAL Integral, TYPE_ASSERVISSEMENT_PID_POS LastValue)
{
    PID->LastTime = Time;
    PID->Integration = Integral;
    PID->LastValue = LastValue;
}

TYPE_ASSERVISSEMENT_PID_RETURN PID_Tick(PID_Data* PID, TYPE_ASSERVISSEMENT_PID_POS Position, TYPE_ASSERVISSEMENT_PID_TIME Time)
{
    TYPE_ASSERVISSEMENT_PID_POS DeltaPos = PID->Target - Position;
    TYPE_ASSERVISSEMENT_PID_TIME DeltaTime = Time - PID->LastTime;
    TYPE_ASSERVISSEMENT_PID_DERIVATIVE Derivative = (Position - PID->LastValue) / DeltaTime;
    PID->Integration += DeltaPos * DeltaTime;
    if (PID->Integration > PID->AbsIMax)
    {
        PID->Integration = PID->AbsIMax;
    }
    else if (PID->Integration < -PID->AbsIMax)
    {
        PID->Integration = -PID->AbsIMax;
    }
    TYPE_ASSERVISSEMENT_PID_RETURN value = PID->P * DeltaPos + PID->I * PID->Integration + PID->D * Derivative;
    PID->LastTime = Time;
    PID->LastValue = Position;
    return value;
}