#include<iostream>
#include<string>
#include<cstdlib>
#include<cmath>
using namespace std;

int polygon_count = 1;

class Point
{
public:
	float x;
	float y;
	Point(float i, float j)
	{
		x = i;
		y = j;
	}
	Point()
	{

	}


};
class Polygon
{
public:
	int point_number = 0;
	Point point[100];

};



float min_x(Polygon p[]);
float max_x(Polygon p[]);
float min_y(Polygon p[]);
float max_y(Polygon p[]);
float min_x(Polygon p);
float max_x(Polygon p);
float min_y(Polygon p);
float max_y(Polygon p);
bool IsCollinear(Point p1, Point p2, Point p3);
Polygon PolygonRemoveRedunancy(Polygon p);
int redunant_points(Polygon p[]);
int redunant_points(Polygon p);
bool IsSamePoint(Point p1, Point p2);
float getdistance(Point p1, Point p2);
float crossproduct(Point p1, Point p2, Point p3);
bool IsPerpendicular(Point p1, Point p2, Point p3);
bool IsParallel(Point p1, Point p2, Point p3, Point p4);

float getarea(Polygon p);
bool IsInRange(Polygon pol1, Polygon pol2, double x, double y);
bool IsIntersectInside(Point p1, Point p2, Point p3, Point p4);
bool IsIntersectOutside(Point p1, Point p2, Point p3, Point p4);
bool pointIsInside(Polygon pol, Point p);
bool polygonIsIntersect(Polygon pol1, Polygon pol2);
void listpolygon(Polygon pol);
bool IsConnected(int start, int end, Polygon p[]);
void MaxIntersect(Polygon p[]);
void MaxConnected(Polygon p[]);
int main()
{
	//declaring variables
	string input_cin = "", temp = "";
	bool x_turn = true;
	int x_order = 0;
	getline(cin, input_cin);
	Polygon p[100];

	//Assigning points to polygon objects from entered string
	for (unsigned int i = 0, j = 0; i < input_cin.length(); i++)
	{
		if (isdigit(input_cin[i]) || input_cin[i] == '.' || input_cin[i] == '-')
			temp += input_cin[i];
		else if (input_cin[i] == ';')
		{

			p[j].point[x_order].y = (float)atof(temp.c_str());
			x_turn = true;
			temp.clear();
			x_order = 0;
			j++;
			polygon_count++;
		}
		if (input_cin[i] == ',' || i == (input_cin.length() - 1))
		{
			if (x_turn)
			{
				p[j].point[x_order].x = (float)atof(temp.c_str());
				p[j].point_number++;
				x_turn = false;
				temp.clear();
			}
			else if (!x_turn)
			{
				p[j].point[x_order].y = (float)atof(temp.c_str());
				x_turn = true;
				temp.clear();
				x_order++;
			}
		}
	}

	//operations
	while (1)
	{
		string input_operation = "";
		getline(cin, input_operation);
		//level 1
		if (input_operation == "Quit")
		{
			break;
		}
		else if (input_operation == "Number_Polygons")
		{
			cout << polygon_count;
		}
		else if (input_operation == "Total_Number_Points")
		{
			int number_points = 0;
			for (int i = 0; i < polygon_count; i++)
				number_points += p[i].point_number;
			cout << number_points;
		}
		else if (input_operation == "Minimum_X")
		{
			cout << min_x(p);
		}
		else if (input_operation == "Maximum_X")
		{
			cout << max_x(p);
		}
		else if (input_operation == "Minimum_Y")
		{
			cout << min_y(p);
		}
		else if (input_operation == "Maximum_Y")
		{
			cout << max_y(p);
		}
		else if (input_operation == "Enclosing_Rectangle")
		{
			cout << "(" << min_x(p) << "," << min_y(p) << ")";
			cout << ",";
			cout << "(" << min_x(p) << "," << max_y(p) << ")";
			cout << ",";
			cout << "(" << max_x(p) << "," << min_y(p) << ")";
			cout << ",";
			cout << "(" << max_x(p) << "," << max_y(p) << ")";
		}
		else if (input_operation == "Total_Redundant_Points")
		{
			cout << redunant_points(p);
		}
		//level 2
		else if (input_operation.find("Polygon_Points") != string::npos)
		{
			string s = input_operation.substr(15);
			int polygon_order = atoi(s.c_str());
			Polygon pol = PolygonRemoveRedunancy(p[polygon_order - 1]);
			listpolygon(pol);

		}
		else if (input_operation.find("Point_Polygons") != string::npos)
		{
			float x, y;
			temp = "";
			for (unsigned int i = 0; i < input_operation.length(); i++)
			{
				if (isdigit(input_operation[i]) || input_operation[i] == '.' || input_operation[i] == '-')
				{
					temp += input_operation[i];
				}
				if (input_operation[i] == ',')
				{
					x = atoi(temp.c_str());
					temp.clear();
				}
				if (input_operation[i] == ')' || i == (input_operation.length() - 1))
				{
					y = atoi(temp.c_str());
					temp = "";
				}

			}

			Point p1(x, y);

			bool polygon_exist = false, first_cout = true, polygons_outted = false;
			for (int i = 0; i < polygon_count; i++) //for every polygon loop
			for (int j = 0; j < p[i].point_number; j++)//for every point in polygon
			{
				if (j == 0)
					polygon_exist = false;
				if (IsSamePoint(p[i].point[j], p1))
					polygon_exist = true;
				if (polygon_exist && j == (p[i].point_number - 1))
				{

					if (first_cout)
					{
						cout << i + 1;
						first_cout = false;
						polygons_outted = true;
					}
					else
					{
						cout << "," << i + 1;
						polygons_outted = true;
					}

				}

			}
			if (!polygons_outted)
			{
				cout << "none";
			}



		}
		else if (input_operation.find("List_Polygons_Points More") != string::npos)
		{
			string s = input_operation.substr(26);
			int point_number = atoi(s.c_str());
			bool first_cout = true, polygons_outted = false;
			for (int i = 0; i < polygon_count; i++)
			{
				int a = redunant_points(p[i]);
				int non_rdp_number = p[i].point_number - redunant_points(p[i]);
				if (non_rdp_number > point_number)
				{

					if (first_cout)
					{
						cout << i + 1;
						first_cout = false;
						polygons_outted = true;
					}
					else
					{
						cout << "," << i + 1;
						polygons_outted = true;
					}
				}
			}


			if (!polygons_outted)
			{
				cout << "none";
			}
		}
		else if (input_operation.find("List_Polygons_Points Less") != string::npos)
		{
			string s = input_operation.substr(26);
			int point_number = atoi(s.c_str());
			bool first_cout = true, polygons_outted = false;
			for (int i = 0; i < polygon_count; i++)
			{
				int a = redunant_points(p[i]);
				int non_rdp_number = p[i].point_number - redunant_points(p[i]);
				if (non_rdp_number < point_number)
				{

					if (first_cout)
					{
						cout << i + 1;
						first_cout = false;
						polygons_outted = true;
					}
					else
					{
						cout << "," << i + 1;
						polygons_outted = true;
					}
				}
			}


			if (!polygons_outted)
			{
				cout << "none";
			}
		}
		else if (input_operation.find("List_Polygons_Points Equal") != string::npos)
		{
			string s = input_operation.substr(27);
			int point_number = atoi(s.c_str());
			bool first_cout = true, polygons_outted = false;
			for (int i = 0; i < polygon_count; i++)
			{
				int a = redunant_points(p[i]);
				int non_rdp_number = p[i].point_number - redunant_points(p[i]);
				if (non_rdp_number == point_number)
				{

					if (first_cout)
					{
						cout << i + 1;
						first_cout = false;
						polygons_outted = true;
					}
					else
					{
						cout << "," << i + 1;
						polygons_outted = true;
					}
				}
			}


			if (!polygons_outted)
			{
				cout << "none";
			}
		}
		else if (input_operation.find("List_Points_Polygons More") != string::npos)
		{
			string s = input_operation.substr(26);
			unsigned int n = atoi(s.c_str()) - 1;
			bool first_cout = true, polygons_outted = false;
			Point used[10000];
			unsigned int used_index = 0;
			for (unsigned int i = 0; i < polygon_count; i++)
			for (unsigned int j = 0; j < p[i].point_number; j++)
			{
				bool notused = true;
				for (unsigned int k = 0; k < used_index; k++)
				if (IsSamePoint(used[k], p[i].point[j]))
				{
					notused = false; break;
				}

				if (notused)
				{
					unsigned int occurence = 0;
					for (unsigned int l = i + 1; l < polygon_count; l++)
					{
						if (l == i) continue;
						for (unsigned int m = 0; m < p[l].point_number; m++)
						{
							if (IsSamePoint(p[i].point[j], p[l].point[m]))
								occurence++;
						}
					}

					if (occurence > n)
					{


						if (first_cout)
						{
							first_cout = false;
							cout << "(" << p[i].point[j].x << "," << p[i].point[j].y << ")";
							polygons_outted = true;
						}
						else
						{
							cout << ",(" << p[i].point[j].x << "," << p[i].point[j].y << ")";
						}


					}
					used[used_index] = p[i].point[j];
					used_index++;
				}
			}

			if (!polygons_outted)
			{
				cout << "none";
			}
		}
		else if (input_operation.find("List_Points_Polygons Less") != string::npos)
		{
			string s = input_operation.substr(26);
			int n = atoi(s.c_str()) - 1;
			bool first_cout = true, polygons_outted = false;
			Point used[10000];
			unsigned int  used_index = 0;
			for (unsigned int i = 0; i < polygon_count; i++)
			for (unsigned int j = 0; j < p[i].point_number; j++)
			{
				bool notused = true;
				//check used before
				for (unsigned int k = 0; k < used_index; k++)
				if (IsSamePoint(used[k], p[i].point[j]))
				{
					notused = false; break;
				}

				if (notused)
				{
					unsigned int occurence = 0;
					for (unsigned int l = i + 1; l < polygon_count; l++)
					{
						if (l == i) continue;
						for (unsigned int m = 0; m < p[l].point_number; m++)
						{
							if (IsSamePoint(p[i].point[j], p[l].point[m]))
								occurence++;
						}
					}

					if (occurence < n )
					{

						if (first_cout)
						{
							first_cout = false;
							cout << "(" << p[i].point[j].x << "," << p[i].point[j].y << ")";
							polygons_outted = true;
						}
						else
						{
							cout << ",(" << p[i].point[j].x << "," << p[i].point[j].y << ")";
						}


					}
					used[used_index] = p[i].point[j];
					used_index++;
				}

			}

			if (!polygons_outted)
			{
				cout << "none";
			}

		}
		else if (input_operation.find("List_Points_Polygons Equal") != string::npos)
		{
			string s = input_operation.substr(27);
			int n = atoi(s.c_str()) - 1;
			bool first_cout = true, polygons_outted = false;
			Point used[10000];
			unsigned int used_index = 0;
			for (unsigned int i = 0; i < polygon_count; i++)
			for (unsigned int j = 0; j < p[i].point_number; j++)
			{
				bool notused = true;
				for (unsigned int k = 0; k < used_index; k++)
				if (IsSamePoint(used[k], p[i].point[j]))
				{
					notused = false; break;
				}

				if (notused)
				{
					unsigned int occurence = 0;
					for (unsigned int l = i + 1; l < polygon_count; l++)
					{
						if (l == i) continue;
						for (unsigned int m = 0; m < p[l].point_number; m++)
						{
							if (IsSamePoint(p[i].point[j], p[l].point[m]))
								occurence++;
						}
					}
					if (occurence == n)
					{


						if (first_cout)
						{
							first_cout = false;
							cout << "(" << p[i].point[j].x << "," << p[i].point[j].y << ")";
							polygons_outted = true;
						}
						else
							cout << ",(" << p[i].point[j].x << "," << p[i].point[j].y << ")";



					}
					used[used_index] = p[i].point[j];
					used_index++;
				}
			}

			if (!polygons_outted)
			{
				cout << "none";
			}

		}
		else if (input_operation.find("Polygon_Perimeter") != string::npos)
		{
			string s = input_operation.substr(18);


			int polygon_order = atoi(s.c_str());
			float perimeter = 0;
			Polygon nrdpol = PolygonRemoveRedunancy(p[polygon_order - 1]);
			for (int i = 0; i < (nrdpol.point_number - 1); i++)
				perimeter += getdistance(nrdpol.point[i], nrdpol.point[i + 1]);
			perimeter += getdistance(nrdpol.point[0], nrdpol.point[nrdpol.point_number - 1]);
			cout << perimeter;

		}
		else if (input_operation == "List_Triangles")
		{
			bool first_cout = true, polygons_outted = false;
			for (int i = 0; i < polygon_count; i++)
			if ((p[i].point_number - redunant_points(p[i])) == 3)
			{
				if (first_cout)
				{
					cout << i + 1;
					first_cout = false;
					polygons_outted = true;
				}
				else
				{
					cout << "," << i + 1;
					polygons_outted = true;
				}
			}
			if (!polygons_outted)
			{
				cout << "none";
			}
		}
		else if (input_operation == "List_Rectangles")
		{

			bool first_cout = true, polygons_outted = false;
			for (unsigned int i = 0; i < polygon_count; i++)
			{
				Polygon nrdpol = PolygonRemoveRedunancy(p[i]);
				unsigned int numberofrightangles = 0;
				if (nrdpol.point_number == 4)
				{
					for (int j = 0; j < (nrdpol.point_number - 2); j++)
					{
						if (IsPerpendicular(nrdpol.point[j], nrdpol.point[j + 1], nrdpol.point[j + 2]))
							numberofrightangles++;

					}
					if (IsPerpendicular(nrdpol.point[nrdpol.point_number - 2], nrdpol.point[nrdpol.point_number - 1], nrdpol.point[0]))
						numberofrightangles++;

					if (IsPerpendicular(nrdpol.point[nrdpol.point_number - 1], nrdpol.point[0], nrdpol.point[1]))
						numberofrightangles++;



					if (numberofrightangles == 4)
					{
						if (first_cout)
						{
							cout << i + 1;
							first_cout = false;
							polygons_outted = true;
						}
						else
						{
							cout << "," << i + 1;
							polygons_outted = true;
						}
					}
				}
			}
			if (!polygons_outted)
			{
				cout << "none";
			}


		}
		else if (input_operation == "List_Trapezoid")
		{


			bool first_cout = true, polygons_outted = false;
			for (int i = 0; i < polygon_count; i++)
			{
				unsigned int numberofparrels = 0;
				Polygon nrdpol = PolygonRemoveRedunancy(p[i]);
				if (nrdpol.point_number == 4)
				{

					if (IsParallel(nrdpol.point[0], nrdpol.point[1], nrdpol.point[2], nrdpol.point[3]))
						numberofparrels++;

					if (IsParallel(nrdpol.point[3], nrdpol.point[0], nrdpol.point[1], nrdpol.point[2]))
						numberofparrels++;

					if (numberofparrels > 0)
					{
						if (first_cout)
						{
							cout << i + 1;
							first_cout = false;
							polygons_outted = true;
						}
						else
						{
							cout << "," << i + 1;
							polygons_outted = true;
						}
					}
				}
			}
			if (!polygons_outted)
			{
				cout << "none";
			}
		}
		//Level 3
		else if (input_operation.find("Inside_Rectangle") != string::npos)
		{
			Polygon rec;
			temp = "";
			x_turn = true;
			x_order = 0;


			for (unsigned int i = 0; i < input_operation.length(); i++)
			{
				if (isdigit(input_operation[i]) || input_operation[i] == '.' || input_operation[i] == '-')
					temp += input_operation[i];
				if (input_operation[i] == ',' || i == (input_operation.length() - 1))
				{
					if (x_turn)
					{
						rec.point[x_order].x = (float)atof(temp.c_str());
						rec.point_number++;
						x_turn = false;
						temp.clear();
					}
					else if (!x_turn)
					{
						rec.point[x_order].y = (float)atof(temp.c_str());
						x_turn = true;
						temp.clear();
						x_order++;
					}
				}
			}

			bool first_cout = true, polygons_outted = false;

			for (unsigned int i = 0; i < polygon_count; i++)
			{
				bool polIsinside = true;
				Polygon nrdpol = PolygonRemoveRedunancy(p[i]);
				for (unsigned int j = 0; j < nrdpol.point_number; j++)
				if (!pointIsInside(rec, nrdpol.point[j]))
				{
					polIsinside = false;
					break;
				}
				if (polIsinside)
				{
					if (first_cout)
					{
						cout << i + 1;
						first_cout = false;
						polygons_outted = true;
					}
					else
					{
						cout << "," << i + 1;
						polygons_outted = true;
					}
				}
			}

			if (!polygons_outted)
				cout << "none";

		}
		else if (input_operation.find("Inside_Circle") != string::npos)
		{

			float x = atof(input_operation.substr(input_operation.find("(") + 1, input_operation.find(",") - input_operation.find("(") - 1).c_str())
				, y = atof(input_operation.substr(input_operation.find(",") + 1, input_operation.find(")") - input_operation.find(",") - 1).c_str())
				, radius = atof(input_operation.substr(input_operation.find(",", input_operation.find(")")) + 1).c_str());
			Point center(x, y);
			bool first_cout = true, polygons_outted = false;
			for (int i = 0; i < polygon_count; i++)
			{
				int pinside = 0;
				Polygon nrdpol = PolygonRemoveRedunancy(p[i]);

				for (int j = 0; j < nrdpol.point_number; j++)
				{
					if (getdistance(nrdpol.point[j], center) <= radius)
					{
						pinside++;
					}
				}
				if (pinside == nrdpol.point_number)
				{
					if (first_cout)
					{
						cout << i + 1;
						first_cout = false;
						polygons_outted = true;
					}
					else
					{
						cout << "," << i + 1;
						polygons_outted = true;
					}
				}

			}
			if (!polygons_outted)
				cout << "none";


		}
		else if (input_operation.find("Polygon_Area") != string::npos)
		{
			string s = input_operation.substr(13);
			int polygon_order = atoi(s.c_str());
			Polygon nrdpol = PolygonRemoveRedunancy(p[polygon_order - 1]);
			cout << getarea(nrdpol);
		}
		else if (input_operation.find("Polygons_Area_Range") != string::npos)
		{
			float min_area, max_area;
			temp = "";

			for (unsigned int i = 0; i < input_operation.length(); i++)
			{
				if (isdigit(input_operation[i]) || input_operation[i] == '.' || input_operation[i] == '-')
				{
					temp += input_operation[i];
				}
				if (input_operation[i] == ',')
				{
					min_area = (float)atof(temp.c_str());
					temp.clear();
				}
				if (input_operation[i] == ')' || i == (input_operation.length() - 1))
				{
					max_area = (float)atof(temp.c_str());
					temp = "";
				}

			}
			bool first_cout = true, polygons_outted = false;
			for (int i = 0; i < polygon_count; i++)
			{
				float area = getarea(p[i]);
				if (area >= min_area && area <= max_area)
				{
					if (first_cout)
					{
						cout << i + 1;
						first_cout = false;
						polygons_outted = true;
					}
					else
					{
						cout << "," << i + 1;
						polygons_outted = true;
					}
				}
			}
			if (!polygons_outted)
				cout << "none";

		}
		else if (input_operation.find("Polygons_Enclosing_Point") != string::npos)
		{
			float x, y;
			temp = "";
			for (unsigned int i = 0; i < input_operation.length(); i++)
			{
				if (isdigit(input_operation[i]) || input_operation[i] == '.' || input_operation[i] == '-')
				{
					temp += input_operation[i];
				}
				if (input_operation[i] == ',')
				{
					x = atoi(temp.c_str());
					temp.clear();
				}
				if (input_operation[i] == ')' || i == (input_operation.length() - 1))
				{
					y = atoi(temp.c_str());
					temp = "";
				}

			}
			Point po(x, y);
			bool first_cout = true, polygons_outted = false;
			for (int i = 0; i < polygon_count; i++)
			{

				if (pointIsInside(p[i], po))
				{
					if (first_cout)
					{
						cout << i + 1;
						first_cout = false;
						polygons_outted = true;
					}
					else
					{
						cout << "," << i + 1;
						polygons_outted = true;
					}
				}
			}
			if (!polygons_outted)
				cout << "none";
		}
		else if (input_operation.find("Is_Intersecting") != string::npos)
		{
			int l, j;

			temp = "";

			for (unsigned int i = 0; i < input_operation.length(); i++)
			{
				if (isdigit(input_operation[i]) || input_operation[i] == '.' || input_operation[i] == '-')
				{
					temp += input_operation[i];
				}
				if (input_operation[i] == ',')
				{
					l = atoi(temp.c_str());
					temp.clear();
				}
				if (input_operation[i] == ')' || i == (input_operation.length() - 1))
				{
					j = atoi(temp.c_str());
					temp = "";
				}

			}

			if (polygonIsIntersect(p[l - 1], p[j - 1]))
				cout << "TRUE";
			else
				cout << "none";


		}
		else if (input_operation.find("Intersecting_Group") != string::npos && input_operation[0] == 'I')
		{

			bool isintergroup = 1;
			unsigned int x[100], index = 0;

			temp = "";

			for (unsigned int i = 0; i < input_operation.length(); i++)
			{
				if (isdigit(input_operation[i]))
					temp += input_operation[i];

				if (input_operation[i] == ',' || i == (input_operation.length() - 1))
				{
					x[index] = atof(temp.c_str());
					index++;
					temp.clear();

				}
			}

			for (unsigned int i = 0; i < index; i++)
			for (unsigned int j = i + 1; j < index; j++)
			{
				bool n = polygonIsIntersect(p[x[i] - 1], p[x[j] - 1]);
				if (!polygonIsIntersect(p[x[i] - 1], p[x[j] - 1]))
				{
					isintergroup = 0;
					break;
				}
			}

			if (isintergroup)
				cout << "TRUE";
			else
				cout << "none";
		}
		else if (input_operation == "Largest_Intersecting_Pair")
		{
			int l = -1, m = -1;
			for (int i = 0; i < polygon_count; i++)
			{
				for (int j = (i + 1); j < polygon_count; j++)
				{
					if (i == j)
						continue;
					if (polygonIsIntersect(p[i], p[j]))
					{
						l = i; m = j;
					}
				}
			}
			if (l != -1 || m != -1)
			{
				for (int i = 0; i < polygon_count; i++)
				{
					for (int j = i + 1; j < polygon_count; j++)
					{
						if (i == j)
							continue;
						if (polygonIsIntersect(p[i], p[j]) && (getarea(p[i]) + getarea(p[j])) >(getarea(p[l]) + getarea(p[m])))
						{
							l = i; m = j;
						}

					}

				}
				cout << l + 1 << "," << m + 1;
			}
			else
				cout << "none";


		}

		//Bonus Level
		else if (input_operation.find("Is_Connected") != string::npos)
		{
			bool isconnectedgroup = 1;
			unsigned int x[100], index = 0;

			temp = "";

			for (unsigned int i = 0; i < input_operation.length(); i++)
			{
				if (isdigit(input_operation[i]))
					temp += input_operation[i];

				if (input_operation[i] == ',' || i == (input_operation.length() - 1))
				{
					x[index] = atof(temp.c_str());
					index++;
					temp.clear();

				}
			}

			for (unsigned int i = 0; i < index; i++)
			for (unsigned int j = i + 1; j < index; j++)
			{

				if (!IsConnected(x[i] - 1, x[j] - 1, p))
				{
					isconnectedgroup = 0;
					break;
				}
			}
			if (isconnectedgroup)
				cout << "TRUE";
			else
				cout << "none";

		}
		else if (input_operation == "Maximum_Intersecting_Group")
		{
			MaxIntersect(p);
		}
		else if (input_operation == "Maximum_Connected_Group")
		{
			MaxConnected(p);
		}


cout << endl;
	}
	return 0;

}
float min_x(Polygon p[])
{
	float min_x = p[0].point[0].x;

	for (int i = 0; i < polygon_count; i++)
	for (int j = 0; j < p[i].point_number; j++)
	if (min_x > p[i].point[j].x)
		min_x = p[i].point[j].x;

	return min_x;
}
float max_x(Polygon p[])
{
	float max_x = p[0].point[0].x;

	for (int i = 0; i < polygon_count; i++)
	for (int j = 0; j < p[i].point_number; j++)
	if (max_x < p[i].point[j].x)
		max_x = p[i].point[j].x;

	return max_x;
}
float min_y(Polygon p[])
{
	float min_y = p[0].point[0].y;

	for (int i = 0; i < polygon_count; i++)
	for (int j = 0; j < p[i].point_number; j++)
	if (min_y > p[i].point[j].y)
		min_y = p[i].point[j].y;

	return min_y;
}
float max_y(Polygon p[])
{
	float max_y = p[0].point[0].y;

	for (int i = 0; i < polygon_count; i++)
	for (int j = 0; j < p[i].point_number; j++)
	if (max_y < p[i].point[j].y)
		max_y = p[i].point[j].y;

	return max_y;
}
float min_x(Polygon p)
{
	float min_x = p.point[0].x;


	for (int j = 0; j < p.point_number; j++)
	if (min_x > p.point[j].x)
		min_x = p.point[j].x;

	return min_x;
}
float max_x(Polygon p)
{
	float max_x = p.point[0].x;


	for (int j = 0; j < p.point_number; j++)
	if (max_x < p.point[j].x)
		max_x = p.point[j].x;

	return max_x;
}
float min_y(Polygon p)
{
	float min_y = p.point[0].y;

	for (int j = 0; j < p.point_number; j++)
	if (min_y > p.point[j].y)
		min_y = p.point[j].y;

	return min_y;
}
float max_y(Polygon p)
{
	float max_y = p.point[0].y;


	for (int j = 0; j < p.point_number; j++)
	if (max_y < p.point[j].y)
		max_y = p.point[j].y;

	return max_y;
}
bool IsSamePoint(Point p1, Point p2)
{
	if (p1.x == p2.x && p1.y == p2.y)
		return true;
	return false;
}
bool IsCollinear(Point p1, Point p2, Point p3)
{
	if (((p2.y - p3.y) / (p2.x - p3.x) == (p1.y - p2.y) / (p1.x - p2.x)))
		return true;
	return false;
}
Polygon PolygonRemoveRedunancy(Polygon p)
{
	Polygon pol1, pol2;
	pol1.point_number = 1;

	pol1.point[0] = p.point[0];
	//removing same points
	for (int i = 1; i < p.point_number; i++)
	if (!IsSamePoint(pol1.point[pol1.point_number - 1], p.point[i]))
	{
		pol1.point[pol1.point_number] = p.point[i];
		pol1.point_number++;
	}
	if (IsSamePoint(p.point[0], p.point[p.point_number - 1]))
		pol1.point_number--;

	//removing collinear points
	pol2.point[0] = pol1.point[0];
	pol2.point_number = 1;
	if (pol1.point_number >1)
	{
		pol2.point[1] = pol1.point[1];
		pol2.point_number++;
		if (IsCollinear(pol1.point[pol1.point_number - 2], pol1.point[pol1.point_number - 1], pol1.point[0]))
		{
			pol1.point_number--;
		}

		for (int i = 2; i < pol1.point_number; i++)
		{
			if (!IsCollinear(pol2.point[pol2.point_number - 2], pol2.point[pol2.point_number - 1], pol1.point[i]))
			{
				pol2.point[pol2.point_number] = pol1.point[i];
				pol2.point_number++;
			}
			else
			{
				pol2.point[pol2.point_number - 1] = pol1.point[i];

			}
		}



	}
	if (IsCollinear(pol2.point[pol2.point_number - 2], pol2.point[pol2.point_number - 1], pol2.point[0]))
	{

		pol2.point_number--;

	}
	if (IsCollinear(pol2.point[pol2.point_number - 1], pol2.point[0], pol2.point[1]))
	{
		for (int i = 1; i < pol1.point_number; i++)
		{
			pol2.point[i - 1] = pol2.point[i];
		}
		pol2.point_number--;

	}
	Polygon pol3;
	pol3.point_number = pol2.point_number;
	for (int i = 0; i < pol2.point_number; i++)
	{
		pol3.point[i] = pol2.point[i];
	}
	return pol3;


}
int redunant_points(Polygon p[])
{

	int rd_p = 0;

	Polygon removedredpol;
	for (int i = 0; i < polygon_count; i++)
	{
		removedredpol = PolygonRemoveRedunancy(p[i]);
		rd_p += p[i].point_number - removedredpol.point_number;

	}

	return rd_p;

}
int redunant_points(Polygon p)
{
	Polygon removedredpol = PolygonRemoveRedunancy(p);
	return p.point_number - removedredpol.point_number;
}
float getdistance(Point p1, Point p2)
{
	return sqrt(pow((p1.x - p2.x), 2) + pow((p1.y - p2.y), 2));
}
bool IsPerpendicular(Point p1, Point p2, Point p3)
{
	Point m1(p2.x - p1.x, p2.y - p1.y);
	Point m2(p3.x - p2.x, p3.y - p2.y);
	float dotproduct = m1.x * m2.x + m1.y * m2.y;
	if (dotproduct == 0)
		return true;
	return false;


}
float crossproduct(Point p1, Point p2)
{
	return (p1.x*p2.y - p1.y*p2.x);
}
bool IsParallel(Point p1, Point p2, Point p3, Point p4)
{
	Point m1(p2.x - p1.x, p2.y - p1.y);
	Point m2(p4.x - p3.x, p4.y - p3.y);

	if (crossproduct(m1, m2) == 0)
		return true;
	return false;


}
float getarea(Polygon p)
{

	p = PolygonRemoveRedunancy(p);
	if (p.point_number > 2)
	{
		float area = 0;
		for (int i = 0; i < p.point_number - 1; i++)
			area += crossproduct(p.point[i], p.point[i + 1]);

		area += crossproduct(p.point[p.point_number - 1], p.point[0]);

		return 0.5 * abs(area);
	}
	else
		return 0;

}
bool IsInRange(Polygon pol1, Polygon pol2, double x, double y)
{
	bool inrange_x = (x <= max_x(pol1) && x <= max_x(pol2) && x >= min_x(pol1) && x >= min_x(pol2));
	bool inrange_y = (y <= max_y(pol1) && y <= max_y(pol2) && y >= min_y(pol1) && y >= min_y(pol2));

	if (inrange_x && inrange_y)
		return true;
	return false;
}
bool IsIntersectInside(Point p1, Point p2, Point p3, Point p4)
{

	Polygon pol1; pol1.point[0] = p1; pol1.point[1] = p2; pol1.point_number = 2;
	Polygon pol2; pol2.point[0] = p3; pol2.point[1] = p4; pol2.point_number = 2;

	double x, y, m1, m2, c1, c2;
	m1 = (p2.y - p1.y) / (p2.x - p1.x);
	m2 = (p4.y - p3.y) / (p4.x - p3.x);
	c1 = p1.y - m1 * p1.x;
	c2 = p3.y - m2 * p3.x;



	//Both lines have m = infinity therefore they are parallel also
	if (p1.x == p2.x && p3.x == p4.x)
	{   //if sameline
		if (p1.x != p3.x)
			return false;
		else
		{
			if (
				(p1.y >= min_y(pol2) && p1.y <= max_y(pol2) ) ||
				(p2.y >= min_y(pol2) && p2.y <= max_y(pol2) ) ||
				(p3.y >= min_y(pol1) && p3.y <= max_y(pol1) ) ||
				(p4.y >= min_y(pol1) && p4.y <= max_y(pol1) )

				)
				return true;
			return false;

		}

	}
	//first line only has m = infinity
	else if (p1.x == p2.x)
	{
		x = p1.x;
		y = m2 *x + c2;

	}
	//second line only has m = infinity
	else if (p3.x == p4.x)
	{
		x = p3.x;
		y = m1 *x + c1;

	}


	//if both lines are parallel 
	else if (m1 == m2)
	{ 
		//if same line
		if (c1 == c2)
		{
			if (
				( p1.y >= min_y(pol2) && p1.y <= max_y(pol2) && p1.x >= min_x(pol2) && p1.x <= max_x(pol2) )  ||
				(p2.y >= min_y(pol2) && p2.y <= max_y(pol2) && p2.x >= min_x(pol2) && p2.x <= max_x(pol2)) ||
				(p3.y >= min_y(pol1) && p3.y <= max_y(pol1) && p3.x >= min_x(pol1) && p3.x <= max_x(pol1)) ||
				(p4.y >= min_y(pol1) && p4.y <= max_y(pol1) && p4.x >= min_x(pol1) && p4.x <= max_x(pol1))

				)
				return true;
			return false;
		}
		//parallel but not same lines will never intersect
		return false;
	}

	//general case x and y values
	else
	{
		x = (c2 - c1) / (m1 - m2);
		y = m1 * x + c1;
	}
	//bool isn = IsInRange(pol1, pol2, x, y);
	//checking the range 
	if (IsInRange(pol1, pol2, x, y))
		return true;
	return false;
}
bool IsIntersectOutside(Point p1, Point p2, Point p3, Point p4)
{

	Polygon pol1; pol1.point[0] = p1; pol1.point[1] = p2; pol1.point_number = 2;
	Polygon pol2; pol2.point[0] = p3; pol2.point[1] = p4; pol2.point_number = 2;

	double x, y, m1, m2, c1, c2;
	m1 = (p2.y - p1.y) / (p2.x - p1.x);
	m2 = (p4.y - p3.y) / (p4.x - p3.x);
	c1 = p1.y - m1 * p1.x;
	c2 = p3.y - m2 * p3.x;



	//Both lines have m = infinity therefore they are parallel also
	if (p1.x == p2.x && p3.x == p4.x)
	{   //if sameline
		if (p1.x != p3.x)
			return false;
		else
		{
			if (p1.y == p3.y || p1.y == p4.y || p2.y == p3.y || p2.y == p4.y)
				return true;
			if (
				(p1.y > min_y(pol2) && p1.y < max_y(pol2)) ||
				(p2.y > min_y(pol2) && p2.y < max_y(pol2)) ||
				(p3.y > min_y(pol1) && p3.y < max_y(pol1)) ||
				(p4.y > min_y(pol1) && p4.y < max_y(pol1))

				)
				return true;
			return false;

		}

	}
	//first line only has m = infinity
	else if (p1.x == p2.x)
	{
		x = p1.x;
		y = m2 *x + c2;

	}
	return true;

}
bool pointIsInside(Polygon pol, Point p)
{
	//this is an old version of the function

	pol = PolygonRemoveRedunancy(pol);
	if ((p.x < min_x(pol)) || (p.x > max_x(pol)) || (p.y < min_y(pol)) || (p.y > max_y(pol)))
		return false;
	else
	{
		bool left_side = false, right_side = false, up_side = false, down_side = false;
		Point pleft(min_x(pol) - 1, p.y), pright(max_x(pol) + 1, p.y), pup(p.x, max_y(pol) + 1), pdown(p.x, min_y(pol) - 1);
		for (int i = 0; i < pol.point_number - 1; i++)
		{
			if (IsIntersectInside(pleft, p, pol.point[i], pol.point[i + 1]))
				left_side = true;
			if (IsIntersectInside(pright, p, pol.point[i], pol.point[i + 1]))
				right_side = true;
			if (IsIntersectInside(pup, p, pol.point[i], pol.point[i + 1]))
				up_side = true;
			if (IsIntersectInside(pdown, p, pol.point[i], pol.point[i + 1]))
				down_side = true;
		}
		if (IsIntersectInside(pleft, p, pol.point[0], pol.point[pol.point_number - 1]))
			left_side = true;
		if (IsIntersectInside(pright, p, pol.point[0], pol.point[pol.point_number - 1]))
			right_side = true;
		if (IsIntersectInside(pup, p, pol.point[0], pol.point[pol.point_number - 1]))
			up_side = true;
		if (IsIntersectInside(pdown, p, pol.point[0], pol.point[pol.point_number - 1]))
			down_side = true;
		if (left_side&&right_side&&up_side&&down_side)
			return true;
		return false;
	}

}
bool pointIsInside(Polygon pol, Point p, bool dummy)
{
	pol = PolygonRemoveRedunancy(pol);
	//checking if point is out of range
	if ((p.x < min_x(pol)) || (p.x > max_x(pol)) || (p.y < min_y(pol)) || (p.y > max_y(pol)))
		return false;
	//if point lies on a side of polygon
	for (unsigned int i = 0; i < pol.point_number-1; i++)
	{
		Polygon twop;
		twop.point_number = 2;
		twop.point[0] = pol.point[i]; twop.point[1] = pol.point[i+1];
		Point p1(pol.point[i].x - p.x, pol.point[i].y - p.y), p2(pol.point[i+1].x - p.x, pol.point[i+1].y - p.y);
		if (p.x <= max_x(twop) && p.x >= min_x(twop) && p.y <= max_y(twop) && p.y >= min_y(twop) && (crossproduct(p1, p2) == 0))
			return true;
	}

	//checking horizontal line intersections
	unsigned int intersection_numbers = 0;
	Point pout(max_x(pol) + 1, p.y);
	for (unsigned int i = 0; i < pol.point_number-1; i++)
	{
		if (IsIntersectInside(p, pout, pol.point[i], pol.point[i + 1]) && p.x != pol.point[i].x)
			intersection_numbers++;
	}
	if (IsIntersectInside(p, pout, pol.point[pol.point_number - 1], pol.point[0]) && p.x != pol.point[0].x)
		intersection_numbers++;
	if (intersection_numbers%2 ==0)
	return false;
	return true;
}
bool polygonIsIntersect(Polygon pol1, Polygon pol2)
{
	pol1 = PolygonRemoveRedunancy(pol1);
	pol2 = PolygonRemoveRedunancy(pol2);
	if (pointIsInside(pol1, pol2.point[0]) || pointIsInside(pol2, pol1.point[0]))
		return true;

	for (int i = 0; i < pol1.point_number - 1; i++)
	{
		for (int j = 0; j < pol2.point_number - 1; j++)
		if (IsIntersectInside(pol1.point[i], pol1.point[i + 1], pol2.point[j], pol2.point[j + 1]))
			return true;
		if (IsIntersectInside(pol1.point[i], pol1.point[i + 1], pol2.point[pol2.point_number - 1], pol2.point[0]))
			return true;
	}
	for (int j = 0; j < pol2.point_number - 1; j++)
	if (IsIntersectInside(pol1.point[pol1.point_number - 1], pol1.point[0], pol2.point[j], pol2.point[j + 1]))
		return true;
	if (IsIntersectInside(pol1.point[pol1.point_number - 1], pol1.point[0], pol2.point[pol2.point_number - 1], pol2.point[0]))
		return true;
	return false;
}
void listpolygon(Polygon pol)
{


	for (int i = 0; i < pol.point_number; i++)
	{
		if (i != (pol.point_number - 1))
			cout << "(" << pol.point[i].x << "," << pol.point[i].y << "),";
		else
			cout << "(" << pol.point[i].x << "," << pol.point[i].y << ")";
	}


}
bool IsInArray(unsigned int m, unsigned int arr[100])
{
	for (unsigned int i = 0; i < 100; i++)
	if (arr[i] == m)
		return true;
	return false;
}
void ConnectedGroup(unsigned int(&ConnectArr)[100][100], Polygon p[])
{
	unsigned int outed[100];
	//initializing coonectarr with 101
	for (unsigned int i = 0; i < 100; i++)
	{
		for (unsigned int j = 0; j < 100; j++)
			ConnectArr[i][j] = 101;
	}
	//declaration of variables
	unsigned int row = 0, colm = 1, outedindex = 0;
	bool iouted = 0;

	for (unsigned int i = 0; i < polygon_count; i++)
	{
		iouted = 0;
		if (IsInArray(i, outed)) continue;

		for (unsigned int j = 0; j < polygon_count; j++)
		{
			if (i == j) continue;

			if (polygonIsIntersect(p[i], p[j]))
			{
				ConnectArr[row][0] = i;
				ConnectArr[row][colm] = j;
				outed[outedindex] = j;
				outedindex++;
				colm++;
				iouted = 1;
			}


		}
		if (iouted == 1)
		{
			outed[outedindex] = i;
			outedindex++;
		for (unsigned int j = 1; j < colm; j++)
		for (unsigned int h = 0; h < polygon_count; h++)
		{
			if (IsInArray(h, outed)) continue;

			if (polygonIsIntersect(p[ConnectArr[row][j]], p[h]))
			{
				ConnectArr[row][colm] = h;
				outed[outedindex] = h;
				outedindex++;
				colm++;
			}
		}


		//initializing variables for next loop
		
			outed[outedindex] = i;
			outedindex++;
			row++;
		}
		colm = 1;
	}

}
bool IsConnected(int start, int end, Polygon p[])
{
	unsigned int connectarr[100][100];

	ConnectedGroup(connectarr, p);

	for (unsigned int i = 0; i < 100; i++)
	{

		if (connectarr[i][0] == 101)
			break;
		if (IsInArray(start, connectarr[i]) && IsInArray(end, connectarr[i]))
			return 1;
	}


	return 0;
}
void fillarray(unsigned int (&arr)[100],unsigned int filling )
{
	for (unsigned int i = 0; i < 100; i++)
		arr[i] = filling;
}
void MaxIntersect(Polygon p[])
{
	unsigned int intersects[100], temparr[100], max_num = 0;

	fillarray(intersects, 101);

	unsigned int index = 0;

	//filling intersects array
	for (unsigned int i = 0; i < polygon_count; i++)
	{

		for (unsigned int j = 0; j < polygon_count; j++)
		{

			if (i == j) continue;

			index = 0;
			fillarray(temparr, 101);
			if (polygonIsIntersect(p[i], p[j]))
			{
				temparr[index] = i;
				index++;
				temparr[index] = j;
				index++;

				for (unsigned int h = 0; h < polygon_count; h++)
				{
					if (h == i || h == j) continue;
					bool intersectsall = 1;
					for (unsigned int o = 0; o <index; o++)
					if (!polygonIsIntersect(p[temparr[o]], p[h]))
					{
						intersectsall = 0; break;
					}
					if (intersectsall)
					{
						temparr[index] = h;
						index++;
					}
				}
				
				//comparing with max 
				if (index > max_num)
				{
					max_num = index;
					for (unsigned int m = 0; m < index; m++)
						intersects[m] = temparr[m];

				}

			}
		}
		
	}





	//printing polygon Ids

	if (intersects[0] != 101)
	{
		cout << intersects[0]+1;
		for (unsigned int i = 1; i < max_num; i++)
			cout << "," << intersects[i] + 1;
	}
	else
		cout << "none";

}
void MaxConnected(Polygon p[])
{
	unsigned int connectarr[100][100]; ConnectedGroup(connectarr, p);
	
	//finding max of intersects array
	unsigned int maxi = 0, max_num = 0;

	for (unsigned int i = 0; i < polygon_count; i++)
	{
		if (connectarr[i][0] == 101) break;

		unsigned int number_connection = 0;

		for (unsigned int j = 0; j < polygon_count; j++)
		{
			if (connectarr[i][j] == 101) break;
			number_connection++;
		}
		if (number_connection>max_num)
		{
			max_num = number_connection; maxi = i;
		}

	}

	//printing polygon Ids

	if (connectarr[maxi][0] != 101)
	{
		cout << connectarr[maxi][0]+1;
		for (unsigned int i = 1; i < max_num; i++)
			cout << "," << connectarr[maxi][i] + 1;
	}
	else
		cout << "none";

}
