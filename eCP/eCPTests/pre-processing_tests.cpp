#include "pch.h"

#include "CppUnitTest.h"
#include "vector"
#include "../eCP/eCP.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace preProcessingTests
{
	TEST_CLASS(preProcessingTests)
	{
	private:
		std::vector<Node*> get_empty_index(unsigned int L = 2) {
			std::vector<Point> S = {
				Point(new float[3] {1, 1, 1}, 0),
				Point(new float[3] {4, 4, 4}, 1),
				Point(new float[3] {2, 2, 2}, 2),
				Point(new float[3] {12, 12, 12}, 3),
				Point(new float[3] {3, 3, 3}, 4),
				Point(new float[3] {9, 9, 9}, 5),
				Point(new float[3] {5, 5, 5}, 6),
				Point(new float[3] {20, 20, 20}, 7),
				Point(new float[3] {17, 17, 17}, 8),
				Point(new float[3] {7, 7, 7}, 9),
				Point(new float[3] {10, 10, 10}, 10),
			};

			return Pre_Processing::create_index(S, L);
		}

	public:

#pragma region get_closest_cluster

		TEST_METHOD(get_closest_cluster_returns_closest_cluster) {
			g_distance_function = &euclidean_distance;
			g_vector_dimensions = 3;

			std::vector<Node*> clusters = {
				new Node(Point(new float[3] {1, 1, 1}, 0)),
				new Node(Point(new float[3] {4, 4, 4}, 1)),
				new Node(Point(new float[3] {7, 7, 7}, 2)),
				new Node(Point(new float[3] {8, 8, 8}, 3)),
			};

			float* query = new float[3]{ 3, 3, 3 };

			Node* actual = Pre_Processing::find_nearest_node(clusters, query);

			Assert::IsTrue(*actual->get_representative() == *new float[3]{ 4, 4, 4 });
		}

		TEST_METHOD(get_closest_cluster_given_query_in_clusters_returns_same) {
			g_distance_function = &euclidean_distance;
			g_vector_dimensions = 3;

			std::vector<Node*> clusters = {
				new Node(Point(new float[3] {1, 1, 1}, 0)),
				new Node(Point(new float[3] {4, 4, 4}, 1)),
				new Node(Point(new float[3] {7, 7, 7}, 2)),
				new Node(Point(new float[3] {8, 8, 8}, 3)),
			};

			float* query = new float[3]{ 8, 8, 8 };

			Node* actual = Pre_Processing::find_nearest_node(clusters, query);

			Assert::IsTrue(*actual->get_representative() == *new float[3]{ 8, 8, 8 });
		}

#pragma endregion

#pragma region create_index_bottom_up

		TEST_METHOD(create_index_bottom_up_creates_empty_datastructure) {
			g_distance_function = &euclidean_distance;
			g_vector_dimensions = 3;

			std::vector<Point> S = {
				Point(new float[3] {1, 1, 1}, 0),
				Point(new float[3] {4, 4, 4}, 1),
				Point(new float[3] {2, 2, 2}, 2),
				Point(new float[3] {3, 3, 3}, 3),
				Point(new float[3] {9, 9, 9}, 4),
				Point(new float[3] {6, 6, 6}, 5)
			};
			unsigned int L = 1;

			auto root = Pre_Processing::create_index(S, L);

			Assert::IsTrue(root.size() != 0);
			for (Node* cluster : root) {
				Assert::IsTrue(cluster->children.size() == 0);
				Assert::IsTrue(cluster->points.size() == 1);
			}
		}

#pragma endregion

#pragma region insert_points

		TEST_METHOD(insert_points_given_empty_index_inserts_points) {
			g_distance_function = &euclidean_distance;
			g_vector_dimensions = 3;

			std::vector<Node*> root = get_empty_index(1);

			std::vector<Point> descriptors = {
				Point(new float[3] {2, 2, 2}, 0),
				Point(new float[3] {9, 9, 9}, 1),
				Point(new float[3] {4, 4, 4}, 2),
				Point(new float[3] {1, 1, 1}, 3),
				Point(new float[3] {12, 12, 12}, 4),
				Point(new float[3] {17, 17, 17}, 5),
				Point(new float[3] {5, 5, 5}, 6),
				Point(new float[3] {3, 3, 3}, 7),
				Point(new float[3] {20, 20, 20}, 8),
				Point(new float[3] {7, 7, 7}, 9),
				Point(new float[3] {10, 10, 10}, 10)
			};

			std::vector<Node*> actual = Pre_Processing::insert_points(root, descriptors);

			for (auto cluster : actual) {
				for (auto leaf : cluster->children) {
					Assert::IsTrue(leaf->points.size() != 0);
				}
			}
		}

#pragma endregion
	};
};