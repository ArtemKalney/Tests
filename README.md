# GraphTest

В данной работе вычисляются полиномы надёжности для средней вероятности связности пары вершин и математического ожидания числа вершин в связанном подграфе, содержащем выделенную вершину, в случайном графе с ненадёжными рёбрами.
В ходе решения использованы как давно известные методы (метод факторизации с предварительными преобразования графа - удаление висячих вершин, параллельно-последовательную редукцию, декомпозицию графов в случае получения точки сочленения), так и новые результаты по использованию цепей с целевыми вершинами. Было реализованно распараллеливание вычислений на уровне связанности графа.

# Зависимости

Для распараллеливания вычислений используется библиотека [MS-MPI](https://docs.microsoft.com/en-us/message-passing-interface/microsoft-mpi?redirectedfrom=MSDN).