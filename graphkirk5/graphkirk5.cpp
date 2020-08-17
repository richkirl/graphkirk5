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

	using string_t = std::string;
	template<typename ElementType>
	class binary_node
	{
	public:
		using node_ptr_t = std::unique_ptr<binary_node>;
		enum class visit_mode : int{ 
			pre_order, 
			in_order, 
			ascending_order = in_order, 
			post_order, 
			descending_order 
		};
	private:
		//ElementType m_index;
		ElementType m_ch;

		binary_node* m_parent;

		node_ptr_t m_left;
		node_ptr_t m_right;
	public:

		string_t get_node_name()
		{
			std::stringstream os;
			os << "node_" << this->m_ch;
			return os.str();
		}

		string_t get_node_definition()
		{
			//node_1[shape = box, label = "Root"];
			std::stringstream os;

			os << get_node_name()
				<< " [ shape = box, label = \" "
				<< this->m_ch << "\"] ;";

			return os.str();
		}

		void print_node(std::stringstream& os)
		{
			os << get_node_definition() << std::endl;
			if (this->m_left)
			{
				os << get_node_name() << " -> " << this->m_left->get_node_name() << "; " << std::endl;

				this->m_left->print_node(os);
			}
			if (this->m_right)
			{
				os << get_node_name() << " -> " << this->m_right->get_node_name() << "; " << std::endl;

				this->m_right->print_node(os);
			}
		}

		string_t build_digraph()
		{
			std::stringstream os;
			os << "digraph G { " << std::endl;
			print_node(os);
			os << "}";
			return os.str();
		}
		ElementType get() const { return this->m_ch; }

		binary_node* find(ElementType value)
		{

			if (value == this->m_ch)
				return this;

			binary_node* ptr = nullptr;

			if (this->m_left && (ptr = this->m_left->find(value)))
				return ptr;

			if (this->m_right && (ptr = this->m_right->find(value)))
				return ptr;

			return nullptr;
		}
		binary_node(ElementType value = ElementType{}, binary_node* parent = nullptr) :
			m_ch{ value }, m_parent{ parent }{}
		bool insert(ElementType value)
		{
			if (value == this->m_ch)
				return false;
			else if (value < this->m_ch)
			{
				if (this->m_left)
					return this->m_left->insert(value);
				else
				{
					this->m_left.reset(new binary_node{ value,this });
					return true;
				}
			}
			else
			{
				if (this->m_right)
					return this->m_right->insert(value);
				else
				{
					this->m_right.reset(new binary_node{ value,this });
					return true;
				}
			}
		}

		template<typename Type, typename... Types>
		bool insert(Type arg, Types... args)
		{
			bool result = this->insert(arg);
			if constexpr (sizeof...(args) != 0)
			{
				return result && this->insert(args...);
			}
			else
				return result;
		}


		void visit_nodes(std::stringstream& os, visit_mode order = visit_mode::in_order)
		{
			switch (order)
			{
			case visit_mode::pre_order:
			{
				os << this->m_ch << std::endl;

				if (this->m_left)
					this->m_left->visit_nodes(os, order);

				if (this->m_right)
					this->m_right->visit_nodes(os, order);

				return;
			}
			case visit_mode::post_order:
			{

				if (this->m_left)
					this->m_left->visit_nodes(os, order);

				if (this->m_right)
					this->m_right->visit_nodes(os, order);

				os << this->m_ch << std::endl;

				return;
			}
			case visit_mode::descending_order:
			{
				if (this->m_right)
					this->m_right->visit_nodes(os, order);

				os << this->m_ch << std::endl;

				if (this->m_left)
					this->m_left->visit_nodes(os, order);

				return;
			}
			case visit_mode::ascending_order:
			default:
			{
				if (this->m_left)
					this->m_left->visit_nodes(os, order);

				os << this->m_ch << std::endl;

				if (this->m_right)
					this->m_right->visit_nodes(os, order);

				return;
			}
			}
		}
	};
	undirectedgraph() :l(0), start(0), finish(0) { };
	~undirectedgraph() { };
	enum class place {
		FREE='.',//46
		SMOKE='?',//63
		WALL= '#',//35
		START='T',//84
		FINISH='C'//67
	};
	enum class dir {
		DOWN,
		RIGHT,
		LEFT,
		UP
	};
	struct mazenode
	{
		mazenode() : x(0), y(0), vertex(0) { };
		~mazenode() { };
		int x;
		int y;
		int vertex;
		bool visited;
	};
	int dirstatetoint(const undirectedgraph::dir& dir);
	void connectnodes(int node1, int node2, unsigned int cost=1);
	template<size_t r, size_t c>
	void mazetograph(mazenode(&mas)[r][c], std::string(&grid)[r][c]);
	//template<unsigned r, unsigned c>
	//void bfsgogoprint(unsigned start, unsigned finish, mazenode(&graph)[r][c]);
	template<unsigned r, unsigned c>
	void bfsgogoprint(unsigned int start, unsigned int finish, mazenode(&graph)[r][c]);
	template<size_t r, size_t c>
	void mazetographst(mazenode(&graph)[r][c], std::string(&grid)[r][c]);
	template<size_t r, size_t c>
	void mazetographst(mazenode(&graph)[r][c], char(&grid)[r][c]);
	void buildgraph(std::map<int, std::vector<std::pair<int, unsigned int>>> myNodes);
	template<size_t r, size_t c>
	void bfsgogoprint(int go, int finish, mazenode(&mas)[r][c]);
	void bfsgogoprint(int go, int finish);
	void test_build_digraph();
	std::map<unsigned int, std::vector<std::pair<unsigned int, unsigned int>>> myNodes;
	std::vector<unsigned int> p;
	dir mState;
	place Pstate;
	unsigned int l, T, C;
	unsigned int start, finish;
private:

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
		{"#","#","#","#","#","#","#","#","#","#","#","#"}};
	//std::string grid[10][30]{
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

	auto it = p.p.rbegin();

	std::cout << "\n\n\n";
	for (; it < p.p.rend(); ++it)
		std::cout << *it << std::endl;
}
void undirectedgraph::test_build_digraph() {
	undirectedgraph::binary_node<int> root;
	using visit_mode = undirectedgraph::binary_node<int>::visit_mode;
	root.insert(4,5,3,2,1,6,7,16,8,19,9,25,10,26,11,27,12,20,13,21,14,22,17,28,23,29,31,30,32,33,24,18,15);
	//std::cout << root.build_digraph() << std::endl;
}
int undirectedgraph::dirstatetoint(const undirectedgraph::dir& dir)
{
	switch (dir) {
	case(undirectedgraph::dir::DOWN):
		return (int)undirectedgraph::dir::DOWN;
	case(undirectedgraph::dir::LEFT):
		return (int)undirectedgraph::dir::LEFT;
	case(undirectedgraph::dir::RIGHT):
		return (int)undirectedgraph::dir::RIGHT;
	case(undirectedgraph::dir::UP):
		return (int)undirectedgraph::dir::UP;
	}
	return -1;
}
void undirectedgraph::connectnodes(int node1, int node2, unsigned int cost)
{
	using nv_t = std::vector<std::pair<int, unsigned int>>;
	nv_t nvt;
	using nvpar_t = std::pair<int, unsigned int>;
	nvpar_t t;
	t.first = node2;
	t.second = cost;
	myNodes[node1].push_back(t);
	myNodes.emplace(node1, node2);
}
void undirectedgraph::buildgraph(std::map<int, std::vector<std::pair<int, unsigned int>>> myNodes)
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
void undirectedgraph::bfsgogoprint(int go, int finish)
{
	//int i = myNodes.find(go)->first;
	//int j = myNodes.find(go)->first;
	//undirectedgraph::p.push_back(i);
	//bool thisfail = false;
	//auto it = undirectedgraph::p.begin();
	//if (i != finish) {
	//	i = myNodes.find(go)->second[0].first;
	//	j = myNodes.find(go)->second[1].first;
	//	for (; it != undirectedgraph::p.end(); ++it)
	//	{
	//		if (*it == i) thisfail = true;
	//	}
	//	if (thisfail) {
	//		std::cout << j << std::endl;
	//		bfsgogoprint(j, finish);
	//	}
	//	if (!thisfail) {
	//		std::cout << i << std::endl;
	//		bfsgogoprint(i, finish);
	//	}
	//	thisfail = false;
	//}
	//int i = myNodes.find(go)->first;//up 3
	//int j = myNodes.find(go)->first;//left 2
	//int k = myNodes.find(go)->first;//down 0
	//int l = myNodes.find(go)->first;//right 1
}
template<size_t r, size_t c>
void undirectedgraph::bfsgogoprint(int start,int finish,mazenode(&graph)[r][c])
{
	unsigned int lenght=0;
	bool visited[500];
	for (int i = 0; i < 500; i++)
	{
		visited[i] = false;
	}
	visited[start] = true;
	std::queue<int> q;
	q.push(start);
	while (q.size() > 0)
	{
		int temp = q.front();
		q.pop();
		for (int i = 0; i < myNodes.find(temp)->second.size(); ++i)
		{
			int neighbor = myNodes.find(temp)->second[i].first;
			if (!visited[neighbor])
			{
				lenght++;
				std::cout << neighbor <<" "<< lenght << std::endl;
				myNodes.find(temp)->second[i].second = lenght;
				visited[neighbor] = true;
				myNodes.find(temp)->second[i].second = lenght;
				if (neighbor == finish) {
					//myNodes.find(finish)->second[i+1].second = lenght;
					q.empty();
					//std::stack<int>fini;
					//fini.push(finish);
					//while (fini.size() > 0)
					//{
					//	int temp = fini.top();
					//	fini.pop();
					//	for (int i = 0; i < myNodes.find(temp)->second.size(); ++i)
					//	{
					//		int nei = myNodes.find(temp)->second[i].first;*/
					//		/*if (myNodes.find(temp)->second[i].second!=1)
					//		{	
					//			if (myNodes.find(temp)->second[i].second)
					//			{
					//				int nei = myNodes.find(temp)->second[i].first;
					//				std::cout << nei << " " << lenght << std::endl;
					//				fini.push(nei);
					//			}*/
							/*	if (myNodes.find(temp)->second[i].second)
								{
									int nei = myNodes.find(temp)->second[i + 1].first;
									std::cout << nei << " " << lenght << std::endl;
									fini.push(nei);
								}*/
					//		}
							//else
							//{
							//	int nei = myNodes.find(temp)->second[i].first;
							//	std::cout << nei << " " << lenght << std::endl;
							//	fini.push(nei);
							//}
						
						//}
					//}
				}
				else {
					q.push(neighbor);
				}
				
			}
		}
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
			if(current !=0&& isdown!=0)
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
	std::cout << " " << "\n\n\n";
	auto it = undirectedgraph::myNodes.begin();
	//for (int i = 1; it != undirectedgraph::myNodes.end(); ++it, ++i) {
	//	std::cout << i << " = ";
	//	for (const auto& pair : undirectedgraph::myNodes[i]) {
	//		std::cout << "\t" << (it->first) << " " << pair.first<<" "<<int(pair.second) << std::endl;
	//	}std::cout << " " << "\n";
	//}
	//buildgraph(myNodes);
	bfsgogoprint(4,33, graph);
	test_build_digraph();
	//int start,finish;
	//std::cout << "Enter start: ";
	//std::cin >> start;
	//std::cout << "Enter finish: ";
	//std::cin >> finish;
	//std::cout << T << " " << C << std::endl;
	//bfsgogoprint(1, 33);
	//bfsgogoprint(C, T);
}
