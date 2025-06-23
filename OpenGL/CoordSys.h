#pragma once
class CoordSys
{
private:

	static CoordSys* inst;

	static int check;

	CoordSys() 
	{

	};

public:
	static const CoordSys& getInstance()
	{
		if (inst == nullptr)
		{
			inst = new CoordSys();
		}
		return *inst;
	};

	static const int getCheck()
	{
		return check;
	}

	static const void setCheck(int newCheck)
	{
		check = newCheck;
	}
};

