#pragma once

const unsigned int TotalShapeSides = 4;
enum class ShapeType { Undefined = -1, Cross, Circle, InArrow, OutArrow };

struct BaseShape
{
	bool      _Inward = false;
	ShapeType _Type = ShapeType::Undefined;
};

struct CrossShape : BaseShape
{
	CrossShape(bool inward)
	{
		_Inward = inward;
		_Type = ShapeType::Cross;
	}
};

struct CircleShape : BaseShape
{
	CircleShape(bool inward)
	{
		_Inward = inward;
		_Type = ShapeType::Circle;
	}
};

struct InArrow : BaseShape
{
	InArrow(bool inward)
	{
		_Inward = inward;
		_Type = ShapeType::InArrow;
	}
};

struct OutArrow : BaseShape
{
	OutArrow(bool inward)
	{
		_Inward = inward;
		_Type = ShapeType::OutArrow;
	}
};


struct Piece
{
public:

	Piece(int index, BaseShape top, BaseShape right, BaseShape bottom, BaseShape left) :
		_Index(index)
	{
		_Sides[0] = top;
		_Sides[1] = right;
		_Sides[2] = bottom;
		_Sides[3] = left;
		_Rotation = 0;
	}

	void RotateCounterClockwise()
	{
		_Rotation++;

		if (_Rotation > 3)
			_Rotation = 0;
	}

	void RotateByValue(int val)
	{
		_Rotation = (_Rotation + val) % 4;
	}

	inline bool CompareRightSide(Piece& other)
	{
		bool bDoesFit = false;

		if (GetRight()._Type == other.GetLeft()._Type &&
			GetRight()._Inward != other.GetLeft()._Inward)
		{
			bDoesFit = true;
		}

		return bDoesFit;
	}

	inline bool CompareBottomSide(Piece& other)
	{
		bool bDoesFit = false;

		if (GetBottom()._Type == other.GetTop()._Type &&
			GetBottom()._Inward != other.GetTop()._Inward)
		{
			bDoesFit = true;
		}

		return bDoesFit;
	}

	inline unsigned int GetSideIndex(int index)
	{
		unsigned short num = index + _Rotation;

		if (num > 3)
			num = num - TotalShapeSides;

		return num;
	}

	BaseShape& GetTop()
	{
		return _Sides[GetSideIndex(0)];
	}

	BaseShape& GetRight()
	{
		return _Sides[GetSideIndex(1)];
	}
	BaseShape& GetBottom()
	{
		return _Sides[GetSideIndex(2)];
	}
	BaseShape& GetLeft()
	{
		return _Sides[GetSideIndex(3)];
	}

	Piece& operator= (Piece& rhs)
	{
		_Rotation = rhs._Rotation;
		_Index = rhs._Index;

		_Sides[0] = rhs._Sides[0];
		_Sides[1] = rhs._Sides[1];
		_Sides[2] = rhs._Sides[2];
		_Sides[3] = rhs._Sides[3];

		return *this;
	}

	inline bool operator==(Piece rhs)
	{
		return _Index == rhs._Index;
	}

	unsigned short _Rotation, _Index;
	BaseShape _Sides[TotalShapeSides];
};
