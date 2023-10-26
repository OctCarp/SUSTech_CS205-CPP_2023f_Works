#include <iostream>
#include <cmath>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAX_TRIANGLES = 100;
const double EPS = 1e-1;

struct Triangle {
    double s1, s2, s3;
};

struct TriangleDictionary {
    Triangle triangles[MAX_TRIANGLES];
    int triangle_count = 0;
};

void addTriangle(TriangleDictionary *dict, double side1, double side2, double angle) {
    double side3 = sqrt(side1 * side1 + side2 * side2 - 2 * side1 * side2 * cos(angle * M_PI / 180));
    Triangle &cur = dict->triangles[dict->triangle_count++];
    cur.s1 = min({side1, side2, side3});
    cur.s3 = max({side1, side2, side3});
    cur.s2 = side1 + side2 + side3 - cur.s1 - cur.s3;
}

bool isSimilar(const Triangle &triangle, double side1, double side2, double side3) {
    double r1 = side1 / triangle.s1;
    double r2 = side2 / triangle.s2;
    double r3 = side3 / triangle.s3;

    return abs(r1 - r2) <= EPS && abs(r1 - r3) <= EPS && abs(r2 - r3) <= EPS;
}

bool searchSimilar(TriangleDictionary *dict, double side1, double side2, double angle) {
    double side3 = sqrt(side1 * side1 + side2 * side2 - 2 * side1 * side2 * cos(angle * M_PI / 180));
    double m1 = min({side1, side2, side3});
    double m3 = max({side1, side2, side3});
    double m2 = side1 + side2 + side3 - m1 - m3;
    for (int i = 0; i < dict->triangle_count; ++i) {
        if (isSimilar(dict->triangles[i], m1, m2, m3)) {
            return true;
        }
    }
    return false;
}

int main() {
    int n;
    // printf("Enter the number of operations (n): ");
    scanf("%d", &n);

    char **actions = (char **) malloc(n * sizeof(char *));
    double **parameters = (double **) malloc(n * sizeof(double *));

    for (int i = 0; i < n; ++i) {
        actions[i] = (char *) malloc(15 * sizeof(char));
        parameters[i] = (double *) malloc(3 * sizeof(double));
    }

    for (int i = 0; i < n; ++i) {
        // printf("Enter operation #%d: ", i + 1);
        scanf("%s", actions[i]);
        if (strcmp(actions[i], "addTriangle") == 0 || strcmp(actions[i], "searchSimilar") == 0) {
            scanf("%lf %lf %lf", &parameters[i][0], &parameters[i][1], &parameters[i][2]);
        }
    }

    TriangleDictionary triangleDictionary;

    for (int i = 0; i < n; ++i) {
        if (strcmp(actions[i], "TriangleDictionary") == 0) {
            // Do nothing
        } else if (strcmp(actions[i], "addTriangle") == 0) {
            addTriangle(&triangleDictionary, parameters[i][0], parameters[i][1], parameters[i][2]);
        } else if (strcmp(actions[i], "searchSimilar") == 0) {
            int result = searchSimilar(&triangleDictionary, parameters[i][0], parameters[i][1], parameters[i][2]);
            printf(result ? "true\n" : "false\n");
        }
    }

    for (int i = 0; i < n; ++i) {
        free(actions[i]);
        free(parameters[i]);
    }
    free(actions);
    free(parameters);

    return 0;
}
