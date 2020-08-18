#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <queue>
#include <stack>
#include <sstream>
class undirectedgraph
{
public:
	undirectedgraph() :l(0), start(0), finish(0), C(0), T(0) { };
	~undirectedgraph() { };
	enum class place {
		FREE = '.',//46
		SMOKE = '?',//63
		WALL = '#',//35
		START = 'T',//84
		FINISH = 'C'//67
	};
	struct mazenode
	{
		mazenode() : x(0), y(0), vertex(0), visited(0) { };
		~mazenode() { };
		int x;
		int y;
		int vertex;
		bool visited;
	};
	void connectnodes(int node1, int node2, unsigned int cost = 1);
	template<size_t r, size_t c>
	void mazetograph(mazenode(&mas)[r][c], std::string(&grid)[r][c]);
	template<size_t r, size_t c>
	void mazetographst(mazenode(&graph)[r][c], std::string(&grid)[r][c]);
	template<size_t r, size_t c>
	void bfsgogoprint(unsigned int start, unsigned int finish, mazenode(&graph)[r][c]);
	std::map<unsigned int, std::vector<std::pair<unsigned int, unsigned int>>> myNodes;
	void printinfoedges(std::map<unsigned int, std::vector<std::pair<unsigned int, unsigned int>>> myNodes);
	template<size_t r, size_t c>
	void printgraph(mazenode(&graph)[r][c]);
	void buildgraph(std::map<unsigned int, std::vector<std::pair<unsigned int, unsigned int>>> myNodes);
private:
	unsigned int l, T, C;
	unsigned int start, finish;
};
int main()
{
	static const unsigned int r = 8, c = 12;
	std::string grid[r][c]{
		{"?","?","?","?","?","?","?","?","?","?","?","?"},
		{"#",".",".",".",".",".","?","?","?","?","?","#"},
		{"#",".","#","#","#","#","#","#","#","#","#","#"},
		{"#",".",".",".",".",".",".",".",".","?",".","#"},
		{"#",".","#","#","#","#","#","#",".","?",".","#"},
		{"#",".","#",".",".",".","#","#",".","?",".","#"},
		{"#",".",".",".","#",".",".",".",".",".",".","#"},
		{"#","#","#","#","#","#","#","#","#","#","#","#"} };
	//std::string grid[r][c]{
	//{"?","?","?","?","?","?","?","?","?","?","?","?","?","?","?","?","?","?","?","?","?","?","?","?","?","?","?","?","?","?"}, // матрица смежности
	//{"#",".",".",".",".",".",".",".",".",".",".",".",".",".",".","?","?","?","?","?","?","?","?","?","?","?","?","?","?","?"},
	//{"#",".","#","#","#","#","#","#","#","#","#","#","#","#","#","?","?","?","?","?","?","?","?","?","?","?","?","?","?","?"},
	//{"#",".",".",".",".",".","T",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".","?","?","?","?"},
	//{"#",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".","#",".","#",".",".","#"},
	//{"#",".","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#",".","#",".",".","#"},
	//{"#",".",".",".",".",".","#","#",".",".",".",".",".",".","#","#",".",".",".",".",".",".","#",".",".",".",".","#","#","#"},
	//{"#",".",".",".","#","#","#","#",".",".","#","#",".",".","#","#",".",".","#","#",".",".","#",".",".","#",".",".",".","#"},
	//{"#",".",".",".",".",".",".",".",".",".","#","#",".",".",".",".",".",".","#","#",".",".",".",".",".","#",".","C",".","#"},
	//{"#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#"} };
	using undrctgrph_t = undirectedgraph;
	undrctgrph_t::mazenode graph[r][c];
	undrctgrph_t p;
	std::cout << "Hello World!\n";
	p.mazetograph(graph, grid);
	//
	p.bfsgogoprint(1, 33, graph);
}
void undirectedgraph::connectnodes(int node1, int node2, unsigned int cost)
{
	using nv_t = std::vector<std::pair<unsigned int, unsigned int>>;
	nv_t nvt;
	using nvpar_t = std::pair<unsigned int, unsigned int>;
	nvpar_t t;
	t.first = node2;
	t.second = cost;
	myNodes[node1].push_back(t);
	myNodes.emplace(node1, node2);
}
void undirectedgraph::buildgraph(std::map<unsigned int, std::vector<std::pair<unsigned int, unsigned int>>> myNodes)
{
	auto it = undirectedgraph::myNodes.begin();
	auto itt = undirectedgraph::myNodes.begin();
	std::cout << "graph {" << "\n";
	for (int i = 1; it != undirectedgraph::myNodes.end(); ++it, ++i) {
		std::cout << "node_" << i << "[label =" << i << "]" << "\n";
	}
	std::cout << "\n\n\n";
	for (int i = 1; itt != undirectedgraph::myNodes.end(); ++itt, ++i) {
		//std::cout << i << " = ";
		for (const auto& pair : undirectedgraph::myNodes[i]) {
			//node_0 -- node_1
			std::cout << "\t" << "node_" << (itt->first) << "--" << " " << "node_" << pair.first << std::endl;
		}std::cout << " " << "\n";
	}
	std::cout << "}" << "\n";
}
template<size_t r, size_t c>
void undirectedgraph::bfsgogoprint(unsigned int start, unsigned int finish, mazenode(&graph)[r][c])
{
	unsigned int lenght = 0;
	unsigned int lenght1 = 0;
	bool visited[500];
	for (int i = 0; i < 500; i++)
	{
		visited[i] = false;
	}
	visited[start] = true;
	std::string paths[50];
	std::string paths1[50];
	std::queue<int> q;
	q.push(start);
	while (q.size() > 0)
	{
		int temp = q.front();
		q.pop();
		for (unsigned int i = 0; i < myNodes.find(temp)->second.size(); ++i)
		{
			paths[i] += "i";
			int neighbor = myNodes.find(temp)->second[i].first;
			if (!visited[neighbor])
			{
				lenght++;
				std::cout << neighbor << " " << lenght <<"\t"<<paths->c_str()<< std::endl;
				myNodes.find(temp)->second[i].second = lenght;
				visited[neighbor] = true;
				myNodes.find(temp)->second[i].second = lenght;
				if (neighbor == finish) {
					//q.empty();
					bool visited1[500];
					for (int i = 0; i < 500; i++)
					{
						visited1[i] = false;
					}
					visited1[finish] = true;
					std::stack<int> qs;
					qs.push(finish);
					while (!qs.empty())
					{
						int temp1 = qs.top();
						qs.pop();
						for (unsigned int i = 0; i < myNodes.find(temp1)->second.size(); ++i)
						{
							paths1[i] += "i";
							int neighbor1 = myNodes.find(temp1)->second[i].first;
							if (!visited1[neighbor1])
							{

								lenght1++;
								std::cout << neighbor1 << " " << lenght1<<"\t" <<paths1->c_str() << std::endl;
								//myNodes.find(temp)->second[i].second = lenght1;
								visited1[neighbor1] = true;
								//myNodes.find(temp)->second[i].second = lenght1;
								if (neighbor1 == start)
								{
									while (!qs.empty())
									{
										qs.pop();
									}
								}
								else {
									qs.push(neighbor1);
								}
							}
						}
					}
				}
				else {
					q.push(neighbor);
				}
			}
		}
	}
}
template<size_t r, size_t c>
void undirectedgraph::printgraph(mazenode(&graph)[r][c])
{

	//for (size_t i = 0; i < r; i++)
	//{
	//	for (size_t y = 0; y < c; y++)
	//	{
	//		
	//		
	//		
	//	std::cout <<"\t"<< graph[i][y].vertex;
	//	}
	//}

}
void undirectedgraph::printinfoedges(std::map<unsigned int, std::vector<std::pair<unsigned int, unsigned int>>> myNodes)
{
	auto it = undirectedgraph::myNodes.begin();
	for (int i = 1; it != undirectedgraph::myNodes.end(); ++it, ++i) {
		std::cout << i << " = ";
		for (const auto& pair : undirectedgraph::myNodes[i]) {
			std::cout << "\t" << (it->first) << " " << pair.first << " " << int(pair.second) << std::endl;
		}std::cout << " " << "\n";
	}
}
template<size_t r, size_t c>
void undirectedgraph::mazetographst(mazenode(&graph)[r][c], std::string(&grid)[r][c])
{
	std::stringstream it;
	int num;
	for (size_t i = 0; i < r; i++)
	{
		for (size_t y = 0; y < c; y++)
		{
			std::string t;
			t += grid[i][y];
			it << t;
			num = (int)*it.str().c_str();
			switch (num)
			{
			case(int(undirectedgraph::place::FREE)):
			{
				this->l++;
				graph[i][y].x = i;
				graph[i][y].y = y;
				graph[i][y].vertex = this->l;
				graph[i][y].visited = false;
				break;
			}
			case(int(undirectedgraph::place::START)):
			{
				this->l++;
				this->T = this->l;
				graph[i][y].x = i;
				graph[i][y].y = y;
				graph[i][y].vertex = this->l;
				graph[i][y].visited = false;
				break;
			}
			case(int(undirectedgraph::place::FINISH)):
			{
				this->l++;
				this->C = this->l;
				graph[i][y].x = i;
				graph[i][y].y = y;
				graph[i][y].vertex = this->l;
				graph[i][y].visited = false;
				break;
			}
			case(int(undirectedgraph::place::WALL)):
			{
				break;
			}
			case(int(undirectedgraph::place::SMOKE)):
			{
				break;
			}
			}
			it.str(""); t.clear();
		}
	}
}
template<size_t r, size_t c>
void undirectedgraph::mazetograph(mazenode(&graph)[r][c], std::string(&grid)[r][c])
{
	mazetographst(graph, grid);
	for (size_t i = 0; i < r; i++)
	{
		for (size_t y = 0; y < c; y++)
		{
			int current = graph[i][y].vertex;
			int isdown = graph[i + 1][y].vertex;
			int isright = graph[i][y + 1].vertex;
			int isup = graph[i - 1][y].vertex;
			int isleft = graph[i][y - 1].vertex;
			if (current != 0 && isdown != 0)
				undirectedgraph::connectnodes(current, isdown);
			if (current != 0 && isright != 0)
				undirectedgraph::connectnodes(current, isright);
			if (current != 0 && isup != 0)
				undirectedgraph::connectnodes(current, isup);
			if (current != 0 && isleft != 0)
				undirectedgraph::connectnodes(current, isleft);

			std::cout << "\t" << current;
		}std::cout << " " << "\n";
	}
	//std::cout << " " << "\n\n\n";

	//buildgraph(myNodes);
	//bfsgogoprint(4, 33, graph);

	//printgraph(graph);
}
