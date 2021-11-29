#pragma once
class Edge
{
public:
	int vertex1;
	int vertex2;

	Edge();

	bool operator<(const Edge& other) const
	{
		if (vertex1 < other.vertex1)
		{
			return true;
		}
		else if (vertex1 == other.vertex1 && vertex2 < other.vertex2)
		{
			return true;
		}

		return false;
	}
};

