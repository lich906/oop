#include <vector>
#include <fstream>
#include <iostream>
#include <optional>
#include <string>
#include <queue>

constexpr auto FIELD_SIZE = 100;
constexpr auto ARGUMENTS_COUNT = 3;

enum class CellType
{
	wall,
	free,
	start,
	end,
	path
};

struct Pos
{
	short x;
	short y;
};

struct Cell
{
	Cell(CellType type)
	{
		this->type = type;
	}

	CellType type;
	short val = 0;
};

typedef std::vector<std::vector<Cell>> Field;

struct Args
{
	std::string inputFilePath;
	std::string outputFilePath;
};

void LogError(const std::string& msg)
{
	std::cout << msg;
}

std::optional<CellType> ReadCell(char ch)
{
	switch (ch)
	{
	case ' ':
		return CellType::free;
	case '#':
		return CellType::wall;
	case 'A':
		return CellType::start;
	case 'B':
		return CellType::end;
	default:
		return std::nullopt;
	}
}

std::optional<CellType> ValidateCell(const std::optional<CellType>& cellType, bool& startFound, bool& endFound)
{
	if (!cellType.has_value())
	{
		LogError("Error: Found invalid symbols while reading labyrinth file.\n");
		return std::nullopt;
	}
	CellType type = cellType.value();
	if (type == CellType::start && startFound)
	{
		LogError("Error: Start position is defined more than once.\n");
		return std::nullopt;
	}
	if (type == CellType::end && endFound)
	{
		LogError("Error: End position is defined more than once.\n");
		return std::nullopt;
	}
	startFound = !startFound ? type == CellType::start : true;
	endFound = !endFound ? type == CellType::end : true;

	return type;
}

void ReadLn(std::istream& in)
{
	char ch;
	while (in.get(ch) && (ch != '\n'));
}

bool Eoln(std::istream& in)
{
	return in.peek() == '\n';
}

void CompleteRow(std::vector<Cell>& row)
{
	while (row.size() != FIELD_SIZE)
	{
		row.push_back(Cell(CellType::free));
	}
}

std::optional<Field> ReadField(std::istream& in)
{
	using namespace std;

	Field field;
	vector<Cell> row;
	char ch;
	optional<CellType> cellType;
	bool startFound = false, endFound = false;

	for (unsigned i = 0; i < FIELD_SIZE && !in.eof(); ++i)
	{
		row.clear();

		for (unsigned j = 0; (j < FIELD_SIZE) && !Eoln(in) && in.get(ch); ++j)
		{
			cellType = ValidateCell(ReadCell(ch), startFound, endFound);
			if (!cellType.has_value())
			{
				return nullopt;
			}

			row.push_back(Cell(cellType.value()));
		}

		CompleteRow(row);
		field.push_back(row);
		ReadLn(in);
	}

	if (!startFound || !endFound)
	{
		LogError("Error: Start or end position was not found.\n");
		return nullopt;
	}

	return field;
}

char GetCellCh(const Cell& cell)
{
	switch (cell.type)
	{
	case CellType::free:
		return ' ';
	case CellType::wall:
		return '#';
	case CellType::start:
		return 'A';
	case CellType::end:
		return 'B';
	case CellType::path:
		return '.';
	default:
		return ' ';
	}
}

bool PrintField(std::ostream& out, Field& field)
{
	for (std::vector<Cell>& row : field)
	{
		for (Cell& cell : row)
		{
			if (!(out << GetCellCh(cell)))
			{
				LogError("Error was occured while writing into output file.\n");
				return false;
			}
		}
		out << '\n';
	}

	return true;
}

std::optional<Args> ParseArgs(int argc, char* argv[])
{
	if (argc != ARGUMENTS_COUNT)
	{
		LogError("Error: Invalid arguments count. Usage: 1-labyrinth.exe <input file> <output file>\n");
		return std::nullopt;
	}

	return { { argv[1], argv[2] } };
}

bool ValidateStreams(std::ifstream& inStream, std::ofstream& outStream)
{
	if (!inStream.is_open())
	{
		LogError("Error was occured while opening input file.\n");
		return false;
	}

	if (!outStream.is_open())
	{
		LogError("Error was occured while opening output file.\n");
		return false;
	}

	return true;
}

Pos GetStartPos(Field& field)
{
	for (short y = 0; y < FIELD_SIZE; ++y)
	{
		for (short x = 0; x < FIELD_SIZE; ++x)
		{
			if (field[y][x].type == CellType::start)
			{
				return { x, y };
			}
		}
	}
}

void TracePath(Field& field, short x, short y, short maxY)
{
	short curVal = field[y][x].val;
	if (!curVal)
	{
		return;
	}

	field[y][x].type = CellType::path;

	if (y - 1 >= 0 && field[y - 1][x].type != CellType::wall && field[y - 1][x].val == (curVal - 1))
	{
		TracePath(field, x, y - 1, maxY);
		return;
	}

	if (x + 1 < FIELD_SIZE && field[y][x + 1].type != CellType::wall && field[y][x + 1].val == (curVal - 1))
	{
		TracePath(field, x + 1, y, maxY);
		return;
	}

	if (y + 1 <= maxY && field[y + 1][x].type != CellType::wall && field[y + 1][x].val == (curVal - 1))
	{
		TracePath(field, x, y + 1, maxY);
		return;
	}

	if (x - 1 >= 0 && field[y][x - 1].type != CellType::wall && field[y][x - 1].val == (curVal - 1))
	{
		TracePath(field, x - 1, y, maxY);
	}
}

bool LabelCell(Field& field, short x, short y, short maxY, short val, std::queue<Pos>& q)
{
	if (y < 0 || x < 0 || y > maxY || x >= FIELD_SIZE || field[y][x].type == CellType::wall || field[y][x].val != 0)
	{
		return false;
	}

	if (field[y][x].type == CellType::end)
	{
		return true;
	}

	field[y][x].val = val;
	q.push({ x, y });

	return false;
}

void Spread(Field& field)
{
	short maxY = field.size() - 1, curVal;
	std::queue<Pos> q;
	Pos curPos;
	q.push(GetStartPos(field));
	
	while (!q.empty())
	{
		curPos = q.front();
		q.pop();
		curVal = field[curPos.y][curPos.x].val;
		if (LabelCell(field, curPos.x + 1, curPos.y, maxY, curVal + 1, q) || 
			LabelCell(field, curPos.x - 1, curPos.y, maxY, curVal + 1, q) || 
			LabelCell(field, curPos.x, curPos.y + 1, maxY, curVal + 1, q) || 
			LabelCell(field, curPos.x, curPos.y - 1, maxY, curVal + 1, q))
		{
			TracePath(field, curPos.x, curPos.y, maxY);
			break;
		}
	}
}

int main(int argc, char* argv[])
{
	using namespace std;

	optional<Args> args = ParseArgs(argc, argv);

	if (!args.has_value())
	{
		return 1;
	}

	ifstream inFile(args->inputFilePath);
	ofstream outFile(args->outputFilePath);

	if (!ValidateStreams(inFile, outFile))
	{
		return 1;
	}

	optional<Field> field = ReadField(inFile);

	if (!field.has_value())
	{
		return 1;
	}

	Field f = field.value();

	Spread(f);

	if (!PrintField(outFile, f))
	{
		return 1;
	}

	return 0;
}
