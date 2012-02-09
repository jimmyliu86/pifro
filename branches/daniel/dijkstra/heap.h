#ifndef _HEAP_H
#define _HEAP_H

#include <stdlib.h>
#include <stdio.h>

#define LOG_HEAP_DEGREE  2

typedef float HeapKeys;

struct Heap {
  int Size;
  int *Index;
  int *Value;
  HeapKeys *Key;
};

inline static Heap* HeapInit(int maxitems) {
  Heap* h = (Heap*) malloc(sizeof(Heap));
  h->Index = (int*) calloc(maxitems, sizeof(int));
  h->Value = (int*) malloc(maxitems * sizeof(int));
  h->Key = (HeapKeys*) malloc(maxitems * sizeof(HeapKeys));
  h->Size = 0;
  return h;
}

inline static void HeapFree(Heap *h) {
  free(h->Index);
  free(h->Value);
  free(h->Key);
  free(h);
}

inline static int HeapSize(Heap *h) {
  return h->Size;
}

inline static void PlaceValue(Heap* h, int value, int index) {
  h->Value[index] = value;
  h->Index[value] = index;
}

inline static int HeapMin(Heap *h) {
  return h->Value[0];
}

inline static void HeapDecKey(Heap *h, int value, HeapKeys key) {
  h->Key[value] = key;
  int iCurrent = h->Index[value];
  for (int iParent = (h->Index[value] - 1) >> LOG_HEAP_DEGREE;
      iCurrent > 0;
      iCurrent = iParent, iParent = (iParent - 1) >> LOG_HEAP_DEGREE ) {
    int nodeParent = h->Value[iParent];
    if (h->Key[value] >= h->Key[nodeParent]) {  // We are in the right place.
      break;
    }
    PlaceValue(h, nodeParent, iCurrent);  // Else move the parent down.
  }
  PlaceValue(h, value, iCurrent );  // Put the node in the hole.
}

inline static void HeapInsert(Heap *h, int value, HeapKeys key) {
  PlaceValue(h, value, h->Size);
  h->Size++;
  HeapDecKey(h, value, key);
}

inline static int Min(const int& a, const int& b) {
  return a < b ? a : b;
}

inline static void HeapDelMin(Heap *h) {
  int iCurrent, iChild, iGoodChild, iFirstChild, iLastChild;
  HeapKeys minValue;
  int node;
  HeapKeys nodekey;
  HeapKeys *key = h->Key;
  int *Value = h->Value;
  h->Size--;
  node = Value[h->Size];
  nodekey = key[node];
  for (iCurrent = 0;
       /* break when value <= min */;
       iCurrent = iGoodChild ) {
    iFirstChild = (iCurrent << LOG_HEAP_DEGREE) + 1;
    iLastChild = Min( iFirstChild + (1 << LOG_HEAP_DEGREE) - 1, h->Size - 1 );
    if ( iFirstChild >= h->Size )  // At the end of the tree.
      break;
    minValue = key[Value[iFirstChild]];
    iGoodChild = iFirstChild;  // The child with the min.
    for (iChild = iFirstChild+1; iChild <= iLastChild; iChild++ )
      if (key[Value[iChild]] < minValue ) {  // New min.
        minValue = key[Value[iChild]];
        iGoodChild = iChild;
      }
    if (nodekey <= minValue) {  // No need to move down-er.
      break;
    }
    PlaceValue(h, Value[iGoodChild], iCurrent );
  }
  PlaceValue(h, node, iCurrent);  // Value goes in hole.
}

inline static void HeapPrint(Heap *h) {
   int iValue, iChild;
   fprintf(stderr, "\nTHE HEAP: size %i", h->Size);
   for ( iValue = 0; iValue < h->Size; iValue++ ) {
      fprintf(stderr,"\npos %i (%i,%lf): ", iValue, h->Value[iValue], h->Key[h->Value[iValue]]);
      for (iChild = (iValue << LOG_HEAP_DEGREE) + 1;
           iChild <= (iValue + 1) << LOG_HEAP_DEGREE  &&  iChild < h->Size;
           iChild++ ) {
         fprintf(stderr, "(%i,%lf) ", h->Value[iChild], h->Key[h->Value[iChild]]);
         if (h->Key[h->Value[iChild]] < h->Key[h->Value[iValue]] ) {
           fprintf(stderr, "** bad bad bad **");
           exit(0);
         }
      }
   }
   fprintf(stderr, "\n\n");
}

#endif
