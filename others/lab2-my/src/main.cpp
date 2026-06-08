#include <iostream>
#include <Vector.h>

#ifdef _WIN32
#include <Windows.h>
#endif

void testConstructors();

void testOperations();

void testMath();

void testIterators();

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif

    std::cout << "=== Конструкторы ===" << std::endl;
    testConstructors();

    std::cout << std::endl << "=== Операции ===" << std::endl;
    testOperations();

    std::cout << std::endl << "=== Математика ===" << std::endl;
    testMath();

    std::cout << std::endl << "=== Итераторы ===" << std::endl;
    testIterators();

    return 0;
}

void testConstructors() {
    const Vector<int> zeros = Vector<int>::zeros(5);
    std::cout << "zeros: " << zeros << std::endl;

    const auto empty = Vector<int>(5);
    std::cout << "empty: " << empty << std::endl;

    auto ones = Vector(1, 5);
    std::cout << "fill:  " << ones << std::endl;

    const auto doubleVec = Vector{1.1, 2.2, 3.3, 4.4};
    std::cout << "init list: " << doubleVec << std::endl;

    Vector<int> intVec(doubleVec);
    std::cout << "cast: " << intVec << std::endl;

    ones = doubleVec;
    std::cout << "assign cast: " << ones << std::endl;

    Vector<char> charV = {'a', 'b', 'c', 'd'};
    std::cout << "char: " << charV << std::endl;
}

void testOperations() {
    const Vector a{1, 2, 3, 4, 5, 6};
    const Vector b{6, 5, 4, 3, 2, 1};
    const Vector c{0.5, 0.4, 0.3, 0.2, 0.1, 0.0};
    std::cout << "a = " << a << std::endl;
    std::cout << "b = " << b << std::endl;
    std::cout << "c = " << c << std::endl;

    std::cout << "a[0] = " << a[0] << std::endl;
    std::cout << "a.get(5) = " << a.get(a.size() - 1) << std::endl;

    std::cout << "a.add(b) = " << a.add(b) << std::endl;
    std::cout << "a.add(10) = " << a.add(10) << std::endl;

    auto d = Vector{1, 1, 1, 1, 1, 1};
    d.addSelf(b);
    std::cout << "d.addSelf(b) = " << d << std::endl;
    d.addSelf(100);
    std::cout << "d.addSelf(100) = " << d << std::endl;

    std::cout << "a + b = " << a + b << std::endl;
    std::cout << "a + c = " << a + c << std::endl;
    std::cout << "a + 1.1 = " << a + 1.1 << std::endl;
    std::cout << "1.1 + a = " << 1.1 + a << std::endl;
    std::cout << "1 + a = " << 1 + a << std::endl;

    std::cout << "a * b = " << a * b << std::endl;
    std::cout << "a * c = " << a * c << std::endl;
    std::cout << "a * 1.1 = " << a * 1.1 << std::endl;
    std::cout << "1.1 * a = " << 1.1 * a << std::endl;
    std::cout << "1 * a = " << 1 * a << std::endl;

    std::cout << "a / b = " << a / b << std::endl;
    std::cout << "a / c = " << a / c << std::endl;
    std::cout << "a / 1.1 = " << a / 1.1 << std::endl;

    std::cout << "a - b = " << a - b << std::endl;
    std::cout << "a - c = " << a - c << std::endl;
    std::cout << "a - 1.1 = " << a - 1.1 << std::endl;
    std::cout << "1.1 - a = " << 1.1 - a << std::endl;
    std::cout << "1 - a = " << 1 - a << std::endl;
}

void testMath() {
    const Vector vectorInt{1, 2, 3, 1, 5, 6};
    std::cout << "vI = " << vectorInt << std::endl;
    const Vector vectorDouble{0.60, 0.30, 0.20, 0.15, 0.12, 0.1};
    std::cout << "vD = " << vectorDouble << std::endl;

    std::cout << "vD & vI = " << (vectorDouble & vectorInt) << std::endl;
    std::cout << "|vD| = " << vectorDouble.magnitude() << std::endl;
    std::cout << "|vI| = " << vectorInt.magnitude() << std::endl;

    Vector eq{1, 2, 3, 4, 5, 6};
    std::cout << "eq = " << eq << std::endl;
    std::cout << "vI == eq: " << (vectorInt == eq) << std::endl;
    std::cout << "vI != eq: " << (vectorInt != eq) << std::endl;

    Vector same{1, 2, 3, 1, 5, 6};
    std::cout << "vI == same: " << (vectorInt == same) << std::endl;
    std::cout << "vI != same: " << (vectorInt != same) << std::endl;

    eq.set(0, 100);
    std::cout << "eq[0]=100: " << eq << std::endl;

    auto zeroVec = Vector<double>::zeros(3);
    std::cout << "zeros.isZero() = " << zeroVec.isZero() << std::endl;
    std::cout << "vD.isZero() = " << vectorDouble.isZero() << std::endl;

    auto norm = vectorDouble.normalized();
    std::cout << "normalized(vD) = " << norm << std::endl;
    std::cout << "|normalized(vD)| = " << norm.magnitude() << std::endl;
    std::cout << "normalized.isUnit() = " << norm.isUnit() << std::endl;
    std::cout << "vD.isUnit() = " << vectorDouble.isUnit() << std::endl;

    Vector mutable_v{3.0, 4.0};
    std::cout << "before normalize: " << mutable_v << std::endl;
    mutable_v.normalize();
    std::cout << "after normalize:  " << mutable_v << std::endl;
    std::cout << "|normalized| = " << mutable_v.magnitude() << std::endl;

    const Vector orig{1, -2, 3};
    std::cout << "orig = " << orig << std::endl;
    std::cout << "-orig = " << -orig << std::endl;
    std::cout << "negate(orig) = " << orig.negate() << std::endl;

    Vector v1{1, 0, 0};
    Vector v2{0.0, 0.5, 0.0};
    std::cout << "v1 = " << v1 << std::endl;
    std::cout << "v2 = " << v2 << std::endl;
    std::cout << "v1 ^ v2 = " << (v1 ^ v2) << std::endl;
    std::cout << "v1 & v2 = " << (v1 & v2) << std::endl;
    std::cout << "angle(v1,v2) = " << v1.angleWith(v2) << std::endl;
    std::cout << "collinear(v1,v2) = " << v1.isCollinearWith(v2) << std::endl;
    std::cout << "orthogonal(v1,v2) = " << v1.isOrthogonalWith(v2) << std::endl;
}

void testIterators() {
    Vector v{10, 20, 30, 40, 50};
    std::cout << "v = " << v << std::endl;

    std::cout << "Forward: ";
    std::ranges::for_each(v, [](const auto& elem) {
        std::cout << elem << " ";
    });
    std::cout << std::endl;

    const auto& cv = v;
    std::cout << "Const forward: ";
    std::ranges::for_each(cv, [](const auto& elem) {
        std::cout << elem << " ";
    });
    std::cout << std::endl;

    std::cout << "Backward: ";
    std::ranges::for_each(std::ranges::reverse_view(v), [](const auto& elem) {
        std::cout << elem << " ";
    });
    std::cout << std::endl;

    std::cout << "Const backward: ";
    std::ranges::for_each(std::ranges::reverse_view(cv), [](const auto& elem) {
        std::cout << elem << " ";
    });
    std::cout << std::endl;

    std::cout << "Range-based for: ";
    for (const auto& elem: v)
        std::cout << elem << " ";
    std::cout << std::endl;

    try {
        auto it = v.end();
        [[maybe_unused]] auto val = *it;
    } catch (const InvalidIteratorError& e) {
        std::cout << "Caught: invalid iterator dereference" << std::endl;
    }

    try {
        Iterator<int> it; {
            Vector tmp{1, 2, 3};
            it = tmp.begin();
        }
        [[maybe_unused]] auto val = *it;
    } catch (const ExpiredDataError& e) {
        std::cout << "Caught: expired data access" << std::endl;
    }
}
