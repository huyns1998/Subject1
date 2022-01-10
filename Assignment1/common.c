#pragma once
#include "common.h"
#include <math.h>
#include<string.h>
#include<stdlib.h>
#define PI 3.14159
/// <summary>
/// Kiểm tra tam giác
/// </summary>
/// <param name="coordinate">Tọa độ các điểm</param>
/// <returns></returns>
bool isTriangle(float* coordinate)
{
	float a, b, c;
	float e, f, g, h, i, l;
	e = coordinate[0];
	f = coordinate[1];
	g = coordinate[2];
	h = coordinate[3];
	i = coordinate[4];
	l = coordinate[5];
	a = distance(e, f, g, h);
	b = distance(e, f, i, l);
	c = distance(g, h, i, l);
	if ((a + b) > c && (b + c) > a && (a + c) > b)
	{
		return true;
	}
	else
	{
		return false;
	}
}
/// <summary>
/// Tính khoảng cách giữa 2 điểm (x1, y1), (x2, y2)
/// </summary>
/// <param name="x1"></param>
/// <param name="y1"></param>
/// <param name="x2"></param>
/// <param name="y2"></param>
/// <returns></returns>
float distance(float x1, float y1, float x2, float y2)
{
	float res = (x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2);
	res = sqrtf(res);
	return res;
}
/// <summary>
/// Tính góc đối của cạnh c
/// </summary>
/// <param name="a">Độ dài cạnh a</param>
/// <param name="b">Độ dài cạnh b</param>
/// <param name="c">Độ dài cạnh c</param>
/// <returns></returns>
float conner(float a, float b, float c)
{
	//Cos(C)
	float resC = (a * a + b * b - c * c) / (2 * a * b);
	//arcos(C)
	resC = acosf(resC);
	//Đổi từ rad->độ
	resC = 180 * resC / PI;
	return resC;
}
/// <summary>
/// Tính độ dài 3 cạnh và 3 góc của tam giác có tọa độ 3 đỉnh cho trước
/// </summary>
/// <param name="coordinate">Tọa độ</param>
/// <returns></returns>
float* triangle(float* coordinate)//Ax, Ay, Bx, By, Cx, Cy
{
	static float res[6];
	res[0] = distance(coordinate[0], coordinate[1], coordinate[2], coordinate[3]);//AB
	res[1] = distance(coordinate[0], coordinate[1], coordinate[4], coordinate[5]);//AC
	res[2] = distance(coordinate[2], coordinate[3], coordinate[4], coordinate[5]);//BC
	res[3] = conner(res[0], res[1], res[2]);//Goc A
	res[4] = conner(res[0], res[2], res[1]);//Goc B
	res[5] = conner(res[1], res[2], res[0]);//Goc C
	return res;
}
/// <summary>
/// Loại tam giác
/// </summary>
/// <param name="connerAndEdge">Mảng chứa các góc và cạnh tam giác</param>
/// <returns></returns>
char* type_triangle(float* connerAndEdge)
{
	static char* res = NULL;
	float a = *(connerAndEdge + 3);
	float b = *(connerAndEdge + 4);
	float c = *(connerAndEdge + 5);
	float AB = *(connerAndEdge);
	float AC = *(connerAndEdge + 1);
	float BC = *(connerAndEdge + 2);
	//Neu la tam giac vuong
		if ((int)a == 90 || (int)b == 90 || (int)c == 90)
		{
			if ((int)a == 90)
			{
				res = "Tam giac ABC vuong tai A\n";
				if ((int)b == 45)
				{
					res = "Tam giac ABC vuong can tai A\n";
				}
			}
			if ((int)b == 90)
			{
				res = "Tam giac ABC vuong tai B\n";
				if ((int)a == 45)
				{
					res = "Tam giac ABC vuong can tai B\n";
				}
			}
			if ((int)c == 90)
			{
				res = "Tam giac ABC vuong tai C\n";
				if ((int)a == 45)
				{
					res = "Tam giac ABC vuong can tai C\n";
				}
			}
		}
		//neu khong la tam giac vuong
		else
		{
			//tam giac deu
			if (AB == AC && AB == BC && AC == BC)
			{
				res = "Tam giac ABC la tam giac deu\n";
			}
			else
			{
				//Tam giac tu
				if ((int)a > 90 || (int)b > 90 || (int)c > 90)
				{
					//tu tai A
					if ((int)a > 90)
					{
						if (AB == AC) 
						{
							res = "Tam giac ABC tu va can tai A\n";
						}
						else
						{
							res = "Tam giac ABC la tam giac tu tai A\n";
						}
					}
					if ((int)b > 90)
					{
						if (AB == BC)
						{
							res = "Tam giac ABC tu va can tai B\n";
						}
						else
						{
							res = "Tam giac ABC la tam giac tu tai B\n";
						}
					}
					if ((int)c > 90)
					{
						if (BC == AC)
						{
							res = "Tam giac ABC tu va can tai C\n";
						}
						else
						{
							res = "Tam giac ABC la tam giac tu tai C\n";
						}
					}
				}
				//Tam giac nhon
				else
				{
					if (AB == AC)
					{
						res = "Tam giac ABC can tai A\n";
					}
					else
					{
						if (AC == BC)
						{
							res = "Tam giac ABC can tai C\n";
						}
						else
						{
							if (AB == BC)
							{
								res = "Tam giac ABC can tai B\n";
							}
							else
							{
								res = "Tam giac ABC nhon\n";
							}
						}
					}
				}
			}
		}
	return res;
}
/// <summary>
/// Diện tích tam giác
/// </summary>
/// <param name="connerAndEdge">Mảng chứa các góc và cạnh tam giác</param>
/// <returns></returns>
float square(float* connerAndEdge)
{
	float a = *(connerAndEdge + 3)*PI/180;
	float AB = *(connerAndEdge);
	float AC = *(connerAndEdge + 1);
	//Công thức tính diện tích: S = 1/2 * AB*AC*sin(A)
	float res = 0.5 * AB * AC * sinf(a);
	return res;
}
/// <summary>
/// Tính đường cao tam giác
/// </summary>
/// <param name="connerAndEdge">Mảng chứa các góc và cạnh tam giác</param>
/// <param name="sqr">Diện tích tam giác</param>
/// <returns></returns>
float* tri_heigh(float* connerAndEdge, float sqr)
{
	static float res[3];
	float AB = *(connerAndEdge);
	float AC = *(connerAndEdge + 1);
	float BC = *(connerAndEdge + 2);
	//hA
	res[0] = 2 * sqr / BC;
	//hB
	res[1] = 2 * sqr / AC;
	//hC
	res[2] = 2 * sqr / AB;

	//sqr = AB*hC/2 => hC = 2*sqr/AB
	return res;
}
/// <summary>
/// Tính trung tuyến tam giác
/// </summary>
/// <param name="connerAndEdge">Mảng chứa các góc và cạnh tam giác</param>
/// <returns></returns>
float* tri_med(float* connerAndEdge)
{
	static float res[3];
	float AB = *(connerAndEdge);
	float AC = *(connerAndEdge + 1);
	float BC = *(connerAndEdge + 2);
	//mA
	res[0] = sqrtf((powf(AB, 2) + powf(AC, 2)) / 2 - powf(BC, 2) / 4);
	//mB
	res[1] = sqrtf((powf(AB, 2) + powf(BC, 2)) / 2 - powf(AC, 2) / 4);
	//mC
	res[2] = sqrtf((powf(AC, 2) + powf(BC, 2)) / 2 - powf(AB, 2) / 4);

	return res;
}
/// <summary>
/// TÌm trọng tâm tam giác
/// </summary>
/// <param name="coordinate">Mảng chứa các góc và cạnh tam giác</param>
/// <returns></returns>
float* tri_center(float* coordinate)
{
	static float res[2];
	//x
	res[0] = (coordinate[0] + coordinate[2] + coordinate[4]) / 3;
	//y
	res[1] = (coordinate[1] + coordinate[3] + coordinate[5]) / 3;

	return res;
}
/// <summary>
/// Hàm chính
/// </summary>
void giaima_tamgiac()
{
	float coordinate[6];
	bool isTri;
	float* connerAndEdge = NULL;
	char* type = NULL;
	float* heigh = NULL;
	float sqr;
	float* med = NULL;
	float* center = NULL;
	printf("Nhap toa do diem A:\n");
	printf("Ax = ");
	scanf("%f", &coordinate[0]);
	printf("Ay = ");
	scanf("%f", &coordinate[1]);

	printf("Nhap toa do diem B:\n");
	printf("Bx = ");
	scanf("%f", &coordinate[2]);
	printf("By = ");
	scanf("%f", &coordinate[3]);

	printf("Nhap toa do diem C:\n");
	printf("Cx = ");
	scanf("%f", &coordinate[4]);
	printf("Cy = ");
	scanf("%f", &coordinate[5]);

	printf("Toa do diem A: (%.2f, %.2f)\n", coordinate[0], coordinate[1]);
	printf("Toa do diem B: (%.2f, %.2f)\n", coordinate[2], coordinate[3]);
	printf("Toa do diem C: (%.2f, %.2f)\n", coordinate[4], coordinate[5]);

	isTri = isTriangle(coordinate);


	if (isTri == true)
	{
		printf("3 diem da nhap vao tao thanh tam giac\n");
		connerAndEdge = triangle(coordinate);
		printf("Do dai canh AB = %.2f\n", *(connerAndEdge));
		printf("Do dai canh AC = %.2f\n", *(connerAndEdge + 1));
		printf("Do dai canh BC = %.2f\n", *(connerAndEdge + 2));
		printf("Goc A = %.2f\n", *(connerAndEdge + 3));
		printf("Goc B = %.2f\n", *(connerAndEdge + 4));
		printf("Goc C = %.2f\n", *(connerAndEdge + 5));

		type = type_triangle(connerAndEdge);

		printf("%s\n", type);

		sqr = square(connerAndEdge);

		printf("Dien tich tam giac ABC = %.2f\n", sqr);

		heigh = tri_heigh(connerAndEdge, sqr);

		printf("Duong cao xuat phat tu diem A = %.2f\n", heigh[0]);
		printf("Duong cao xuat phat tu diem B = %.2f\n", heigh[1]);
		printf("Duong cao xuat phat tu diem C = %.2f\n", heigh[2]);

		med = tri_med(connerAndEdge);

		printf("Trung tuyen xuat phat tu diem A = %.2f\n", med[0]);
		printf("Trung tuyen xuat phat tu diem B = %.2f\n", med[1]);
		printf("Trung tuyen xuat phat tu diem C = %.2f\n", med[2]);

		center = tri_center(coordinate);

		printf("Toa do trong tam tam giac ABC la [%.2f, %.2f]\n", center[0], center[1]);
	}
	else
	{
		printf("3 diem da nhap vao KHONG tao thanh tam giac\n");
	}
	printf("-------------------------------------------\n");
}