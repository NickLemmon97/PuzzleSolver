#include "PuzzleSolver.h"
#include <string>
#include <sstream>
#include <fstream>

PuzzleSolver::PuzzleSolver()
{
	_Shapes[0] = CrossShape (false);
	_Shapes[1] = CrossShape (true );
	_Shapes[2] = CircleShape(false);
	_Shapes[3] = CircleShape(true );
	_Shapes[4] = InArrow    (false);
	_Shapes[5] = InArrow    (true );
	_Shapes[6] = OutArrow   (false);
	_Shapes[7] = OutArrow   (true );

	DrawFunc = nullptr;
}

PuzzleSolver::~PuzzleSolver()
{

}

void PuzzleSolver::GenerateDefaultLayout()
{
	//Top row of pieces
	_Pieces.emplace_back(1, _Shapes[7], _Shapes[0], _Shapes[4], _Shapes[5]);
	_Pieces.emplace_back(2, _Shapes[7], _Shapes[2], _Shapes[4], _Shapes[5]);
	_Pieces.emplace_back(3, _Shapes[7], _Shapes[6], _Shapes[4], _Shapes[3]);
	_Pieces.emplace_back(4, _Shapes[3], _Shapes[0], _Shapes[6], _Shapes[7]);

	//2nd row of pieces
	_Pieces.emplace_back(5, _Shapes[1], _Shapes[4], _Shapes[2], _Shapes[5]);
	_Pieces.emplace_back(6, _Shapes[3], _Shapes[2], _Shapes[6], _Shapes[1]);
	_Pieces.emplace_back(7, _Shapes[3], _Shapes[6], _Shapes[6], _Shapes[5]);
	_Pieces.emplace_back(8, _Shapes[3], _Shapes[2], _Shapes[6], _Shapes[7]);

	//Third row of pieces
	_Pieces.emplace_back(9, _Shapes[3], _Shapes[2], _Shapes[2], _Shapes[7]);
	_Pieces.emplace_back(10, _Shapes[7], _Shapes[4], _Shapes[4], _Shapes[1]);
	_Pieces.emplace_back(11, _Shapes[3], _Shapes[2], _Shapes[0], _Shapes[1]);
	_Pieces.emplace_back(12, _Shapes[5], _Shapes[0], _Shapes[2], _Shapes[3]);

	//Fourth row of pieces
	_Pieces.emplace_back(13, _Shapes[3], _Shapes[4], _Shapes[4], _Shapes[1]);
	_Pieces.emplace_back(14, _Shapes[1], _Shapes[6], _Shapes[0], _Shapes[5]);
	_Pieces.emplace_back(15, _Shapes[7], _Shapes[4], _Shapes[0], _Shapes[7]);
	_Pieces.emplace_back(16, _Shapes[3], _Shapes[4], _Shapes[2], _Shapes[1]);
}

void PuzzleSolver::GenerateLayoutFromFile(const char* filepath)
{
	std::fstream File(filepath);

	if (File.is_open())
	{
		std::string str;
		while (std::getline(File, str))
		{
			std::istringstream stream(str);

			int i, t, r, b, l;
			i = _Pieces.size() + 1;

			std::string s;

			getline(stream, s, ' ');
			t = atoi(s.c_str());

			getline(stream, s, ' ');
			r = atoi(s.c_str());

			getline(stream, s, ' ');
			b = atoi(s.c_str());

			getline(stream, s, ' ');
			l = atoi(s.c_str());

			_Pieces.emplace_back(i, _Shapes[t], _Shapes[r], _Shapes[b], _Shapes[l]);
		}

		File.close();
	}
}

void PuzzleSolver::GenerateLayoutFromIntArr(int* dataArr)
{
	int count = 16 * 4; //16 pieces with 4 different sides
	for(int p = 0; p < count; p+=4)
	{
		int i, t, r, b, l;
		i = _Pieces.size() + 1;

		t = dataArr[p];
		r = dataArr[p+1];
		b = dataArr[p+2];
		l = dataArr[p+3];

		_Pieces.emplace_back(i, _Shapes[t], _Shapes[r], _Shapes[b], _Shapes[l]);
	}
}

void PuzzleSolver::SolvePuzzle()
{
	//Discover all the sets of 2
	std::vector<std::vector<Piece>> SetsOf2;

	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			if (_Pieces[i] == _Pieces[j]) continue;

			Piece tempi = _Pieces[i];
			for (int irot = 0; irot < 4; irot++)
			{
				Piece tempj = _Pieces[j];

				if (tempi.CompareRightSide(tempj))
				{
					std::vector<Piece> vec;
					vec.push_back(tempi);
					vec.push_back(tempj);
					SetsOf2.push_back(vec);
				}

				tempj.RotateCounterClockwise();

				if (tempi.CompareRightSide(tempj))
				{
					std::vector<Piece> vec;
					vec.push_back(tempi);
					vec.push_back(tempj);
					SetsOf2.push_back(vec);
				}

				tempj.RotateCounterClockwise();

				if (tempi.CompareRightSide(tempj))
				{
					std::vector<Piece> vec;
					vec.push_back(tempi);
					vec.push_back(tempj);
					SetsOf2.push_back(vec);
				}

				tempj.RotateCounterClockwise();

				if (tempi.CompareRightSide(tempj))
				{
					std::vector<Piece> vec;
					vec.push_back(tempi);
					vec.push_back(tempj);
					SetsOf2.push_back(vec);
				}

				tempi.RotateCounterClockwise();

			} //for irot
		}//for j
	}//for i


	/*
		i0 i1 j0 j1
		k0 k1 l0 l1
		m0 m1 n0 n1
		o0 o1 p0 p1
	*/

	for (int i = 0; i < SetsOf2.size(); i++)
	{
		for (int j = 0; j < SetsOf2.size(); j++)
		{
			if (!IsUniqueSetOf2(SetsOf2[i], SetsOf2[j])) continue;
			if (!SetsOf2[i][1].CompareRightSide(SetsOf2[j][0])) continue;

			for (int k = 0; k < SetsOf2.size(); k++)
			{
				if (!IsUniqueSetOf2(SetsOf2[k], SetsOf2[j])) continue;
				if (!IsUniqueSetOf2(SetsOf2[i], SetsOf2[k])) continue;
				if (!SetsOf2[i][0].CompareBottomSide(SetsOf2[k][0])) continue;
				if (!SetsOf2[i][1].CompareBottomSide(SetsOf2[k][1])) continue;

				for (int l = 0; l < SetsOf2.size(); l++)
				{
					if (!IsUniqueSetOf2(SetsOf2[l], SetsOf2[j])) continue;
					if (!IsUniqueSetOf2(SetsOf2[i], SetsOf2[l])) continue;
					if (!IsUniqueSetOf2(SetsOf2[k], SetsOf2[l])) continue;
					if (!SetsOf2[k][1].CompareRightSide(SetsOf2[l][0])) continue;
					if (!SetsOf2[j][0].CompareBottomSide(SetsOf2[l][0])) continue;
					if (!SetsOf2[j][1].CompareBottomSide(SetsOf2[l][1])) continue;

					for (int m = 0; m < SetsOf2.size(); m++)
					{
						if (!IsUniqueSetOf2(SetsOf2[m], SetsOf2[j])) continue;
						if (!IsUniqueSetOf2(SetsOf2[i], SetsOf2[m])) continue;
						if (!IsUniqueSetOf2(SetsOf2[k], SetsOf2[m])) continue;
						if (!IsUniqueSetOf2(SetsOf2[l], SetsOf2[m])) continue;
						if (!SetsOf2[k][0].CompareBottomSide(SetsOf2[m][0])) continue;
						if (!SetsOf2[k][1].CompareBottomSide(SetsOf2[m][1])) continue;

						for (int n = 0; n < SetsOf2.size(); n++)
						{
							if (!IsUniqueSetOf2(SetsOf2[n], SetsOf2[j])) continue;
							if (!IsUniqueSetOf2(SetsOf2[i], SetsOf2[n])) continue;
							if (!IsUniqueSetOf2(SetsOf2[k], SetsOf2[n])) continue;
							if (!IsUniqueSetOf2(SetsOf2[l], SetsOf2[n])) continue;
							if (!IsUniqueSetOf2(SetsOf2[m], SetsOf2[n])) continue;
							if (!SetsOf2[m][1].CompareRightSide(SetsOf2[n][0])) continue;
							if (!SetsOf2[l][0].CompareBottomSide(SetsOf2[n][0])) continue;
							if (!SetsOf2[l][1].CompareBottomSide(SetsOf2[n][1])) continue;

							for (int o = 0; o < SetsOf2.size(); o++)
							{
								if (!IsUniqueSetOf2(SetsOf2[o], SetsOf2[j])) continue;
								if (!IsUniqueSetOf2(SetsOf2[i], SetsOf2[o])) continue;
								if (!IsUniqueSetOf2(SetsOf2[k], SetsOf2[o])) continue;
								if (!IsUniqueSetOf2(SetsOf2[l], SetsOf2[o])) continue;
								if (!IsUniqueSetOf2(SetsOf2[m], SetsOf2[o])) continue;
								if (!IsUniqueSetOf2(SetsOf2[n], SetsOf2[o])) continue;
								if (!SetsOf2[m][0].CompareBottomSide(SetsOf2[o][0])) continue;
								if (!SetsOf2[m][1].CompareBottomSide(SetsOf2[o][1])) continue;

								for (int p = 0; p < SetsOf2.size(); p++)
								{
									if (!IsUniqueSetOf2(SetsOf2[p], SetsOf2[j])) continue;
									if (!IsUniqueSetOf2(SetsOf2[i], SetsOf2[p])) continue;
									if (!IsUniqueSetOf2(SetsOf2[k], SetsOf2[p])) continue;
									if (!IsUniqueSetOf2(SetsOf2[l], SetsOf2[p])) continue;
									if (!IsUniqueSetOf2(SetsOf2[m], SetsOf2[p])) continue;
									if (!IsUniqueSetOf2(SetsOf2[n], SetsOf2[p])) continue;
									if (!IsUniqueSetOf2(SetsOf2[o], SetsOf2[p])) continue;
									if (!SetsOf2[o][1].CompareRightSide(SetsOf2[p][0])) continue;
									if (!SetsOf2[n][0].CompareBottomSide(SetsOf2[p][0])) continue;
									if (!SetsOf2[n][1].CompareBottomSide(SetsOf2[p][1])) continue;

									//Finally if we have made it here we have found a solution

									std::vector<Piece> sol;
									sol.push_back(SetsOf2[i][0]);
									sol.push_back(SetsOf2[i][1]);
									sol.push_back(SetsOf2[j][0]);
									sol.push_back(SetsOf2[j][1]);
									sol.push_back(SetsOf2[k][0]);
									sol.push_back(SetsOf2[k][1]);
									sol.push_back(SetsOf2[l][0]);
									sol.push_back(SetsOf2[l][1]);
									sol.push_back(SetsOf2[m][0]);
									sol.push_back(SetsOf2[m][1]);
									sol.push_back(SetsOf2[n][0]);
									sol.push_back(SetsOf2[n][1]);
									sol.push_back(SetsOf2[o][0]);
									sol.push_back(SetsOf2[o][1]);
									sol.push_back(SetsOf2[p][0]);
									sol.push_back(SetsOf2[p][1]);
									_Solutions.push_back(sol);

								}//int p = second 2, last row
							}//int  o = first 2, last row
						}//int n = second 2 third row
					}//int m = first 2, third row
				}//Int l = second 2, second row
			}//Int k = first 2, second row
		}//Int j = second 2, top row
	}//Int i = first 2, top row

	/*
		i0 i1 j0 j1
		k0 k1 l0 l1
		m0 m1 n0 n1
		o0 o1 p0 p1
	*/
}

int PuzzleSolver::GetNumSolutions()
{
	return _Solutions.size();
}

Piece PuzzleSolver::GetPieceAtIndex(int index)
{
	return _Pieces[index];
}

Piece* PuzzleSolver::GetSolutionAtIndex(int index)
{
	return _Solutions[index].data();
}

void PuzzleSolver::SetDrawFunction(InternalDrawFunc func)
{
	DrawFunc = func;
}

void PuzzleSolver::DrawSolutions()
{
	if (DrawFunc != nullptr)
	{
		for (std::vector<Piece> sol : _Solutions)
		{
			DrawFunc(sol);
		}
	}
}
