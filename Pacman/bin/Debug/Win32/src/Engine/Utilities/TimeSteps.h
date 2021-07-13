#pragma once

class TimeSteps
{
private:
	TimeSteps() {};
	~TimeSteps() {}
public:
	static void Update();
	static float GetTimeSteps() { return Ts; }
private:
	static float Ts;
	static float CurrentFrame;
	static float LastFrame;
};