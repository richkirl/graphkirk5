#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <queue>
#include <stack>
#include <sstream>
#include <memory>
class undirectedgraph
{
public:
	undirectedgraph() :l(0), start(0), finish(0), C(0), T(0) { };
	~undirectedgraph() { };
	//------------------------------------------------------------------------------------------------------------//place for construction space  from labirynth to graph
	enum class place {
		FREE = '.',//46
		SMOKE = '?',//63
		WALL = '#',//35
		START = 'T',//84
		FINISH = 'C'//67
	};
	//---------------------------------------------------------------------------------------------------------------//mazenode for first step work with later graph
	struct mazenode
	{
		mazenode() : x(0), y(0), vertex(0), visited(0) { };
		~mazenode() { };
		int x;
		int y;
		int vertex;
		bool visited;
	};
	//------------------------------------------------------------------------------------------------------------//conection edges
	void connectnodes(int node1, int node2, unsigned int cost = 1);
	//------------------------------------------------------------------------------------------------------------//send mas and initialization first step for work with graph
	template<size_t r, size_t c>
	void mazetograph(mazenode(&mas)[r][c], std::string(&grid)[r][c]);
	template<size_t r, size_t c>
	void mazetographst(mazenode(&graph)[r][c], std::string(&grid)[r][c]);
	//------------------------------------------------------------------------------------------------------------//working algo
	void bfsgogoprint(unsigned int start, unsigned int finish);
	void stopstackqueue(std::stack<unsigned int> x, std::queue<unsigned int> y, int flag );
	void dfsturn(unsigned int start, unsigned int finish);
	//------------------------------------------------------------------------------------------------------------//known my graph struxture
	std::map<unsigned int, std::vector<std::pair<unsigned int, unsigned int>>> myNodes;
	//------------------------------------------------------------------------------------------------------------//visualisations methods
	void printinfoedges(std::map<unsigned int, std::vector<std::pair<unsigned int, unsigned int>>> myNodes);
	void buildgraph(std::map<unsigned int, std::vector<std::pair<unsigned int, unsigned int>>> myNodes);
private:
	unsigned int l, T, C;
	unsigned int start, finish;
	//------------------------------------------------------------------------------------------------------------//bfs
	using array_ptr_type = std::unique_ptr<unsigned int>;
	using array_ptr_type2 = std::unique_ptr<unsigned int[]>;
	using array_ptr_type1 = std::unique_ptr<bool[]>;
	array_ptr_type lenght = array_ptr_type(new unsigned int(0));
	array_ptr_type1 visited = array_ptr_type1(new bool[500]);
	unsigned int paths[50];
	std::queue<unsigned int> q;
	//------------------------------------------------------------------------------------------------------------//dfs
	array_ptr_type lenght1 = array_ptr_type(new unsigned int(0));
	array_ptr_type1 visited1 = array_ptr_type1(new bool[500]);
	unsigned int paths1[50];
	std::stack<unsigned int> qs;
};
int main()
{
	static const unsigned int r = 10, c = 30;
	//std::string grid[r][c]{
	//	{"?","?","?","?","?","?","?","?","?","?","?","?"},
	//	{"#",".",".",".",".",".","?","?","?","?","?","#"},
	//	{"#",".","#","#","#","#","#","#","#","#","#","#"},
	//	{"#",".",".",".",".",".",".",".",".","?",".","#"},
	//	{"#",".","#","#","#","#","#","#",".","?",".","#"},
	//	{"#",".","#",".",".",".","#","#",".","?",".","#"},
	//	{"#",".",".",".","#",".",".",".",".",".",".","#"},
	//	{"#","#","#","#","#","#","#","#","#","#","#","#"} };
	std::string grid[r][c]{
	{"?","?","?","?","?","?","?","?","?","?","?","?","?","?","?","?","?","?","?","?","?","?","?","?","?","?","?","?","?","?"}, // матрица смежности
	{"#",".",".",".",".",".",".",".",".",".",".",".",".",".",".","?","?","?","?","?","?","?","?","?","?","?","?","?","?","?"},
	{"#",".","#","#","#","#","#","#","#","#","#","#","#","#","#","?","?","?","?","?","?","?","?","?","?","?","?","?","?","?"},
	{"#",".",".",".",".",".","T",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".","?","?","?","?"},
	{"#",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".","#",".","#",".",".","#"},
	{"#",".","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#",".","#",".",".","#"},
	{"#",".",".",".",".",".","#","#",".",".",".",".",".",".","#","#",".",".",".",".",".",".","#",".",".",".",".","#","#","#"},
	{"#",".",".",".","#","#","#","#",".",".","#","#",".",".","#","#",".",".","#","#",".",".","#",".",".","#",".",".",".","#"},
	{"#",".",".",".",".",".",".",".",".",".","#","#",".",".",".",".",".",".","#","#",".",".",".",".",".","#",".","C",".","#"},
	{"#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#"}};
	using undrctgrph_t = undirectedgraph;
	undrctgrph_t::mazenode graph[r][c];
	undrctgrph_t p;
	p.mazetograph(graph, grid);
	p.bfsgogoprint(1, 130);
	//p.dfsturn(1, 130);
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

void undirectedgraph::bfsgogoprint(unsigned int start, unsigned int finish)
{
	for (int i = 0; i < 500; i++)
	{
		visited[i] = false;
	}
	visited[start] = true;
	q.push(start);
	while (q.size() > 0)
	{
		int temp = q.front();
		q.pop();
		for (unsigned int i = 0; i < myNodes.find(temp)->second.size(); ++i)
		{
			paths[i]++;
			int neighbor = myNodes.find(temp)->second[i].first;
			if (!visited[neighbor])
			{
				(*lenght)++;
				std::cout << neighbor << "\t" << *lenght << "\t" << paths[i] << std::endl;
				myNodes.find(temp)->second[i].second = paths[i];
				visited[neighbor] = true;
				myNodes.find(temp)->second[i].second = paths[i];
				if (neighbor == finish) {
					q.swap(q);
					stopstackqueue(qs, q, 2);
					dfsturn(1, 130);
				}
				else {
					q.push(neighbor);
				}
			}
		}
	}
	//dfsturn(1, 130);
}
void undirectedgraph::stopstackqueue(std::stack<unsigned int> x, std::queue<unsigned int> y, int flag)
{
	switch (flag)
	{
	case(1):
	{
		while (!x.empty())
		{
			//x.pop();
			while (!x.empty())
			{
				std::stack<unsigned int>().swap(x);
			}
		}
	}
	case(2):
	{
		while (!y.empty())
		{
			y.pop();
			//y=std::stack<unsigned int>();
		}
	}
	}
}
void undirectedgraph::dfsturn(unsigned int start, unsigned int finish)
{
	visited1[129] = true;
	for (int i = 0; i < 500; i++)
	{
		visited1[i] = false;
	}
	qs.push(129);
	while (!qs.empty())
	{
		int temp1 = qs.top();
		qs.pop();
		for (unsigned int i = 0; i < myNodes.find(temp1)->second.size(); ++i)
		{
			paths1[i]++;
			int neighbor1 = myNodes.find(temp1)->second[i].first;
			if (!visited1[neighbor1])
			{
				(*lenght1)++;
				std::cout << neighbor1 << "\t" << *lenght1 << "\t" << paths1[i] << std::endl;
				visited1[neighbor1] = true;
				if (neighbor1 == 1)
				{
					std::stack<unsigned int>().swap(qs);
					//qs.empty();
					stopstackqueue(qs,q,1);
				}
				else {
					qs.push(neighbor1);
				}
			}
		}
	}
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
			if (isdown == false)
			{
				isdown = false;
			}
			int isright = graph[i][y + 1].vertex;
			if (isright == false)
			{
				isright = false;
			}
			int isup = graph[i - 1][y].vertex;
			if (isup == false)
			{
				isup = false;
				//current = false;
			}
			int isleft = graph[i][y - 1].vertex;
			if (isleft == false)
			{
				isleft = false;
				//current = false;
			}
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
