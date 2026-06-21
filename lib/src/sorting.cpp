// Implementación de la librería de ordenamiento
// Los templates están completamente definidos en los headers
// Este archivo existe para permitir compilación de la librería como .so/.dll
#include "sorting.h"

// Explícitamente instantiamos algunos tipos comunes para precompilación
template void ordenar<int>(Array<int>&);
template void ordenar<double>(Array<double>&);
template void quickSort<int>(Array<int>&);
template void quickSort<double>(Array<double>&);
