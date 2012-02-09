#ifndef _HEAP_H
#define _HEAP_H

#include <stdlib.h>
#include <stdio.h>

#define LOG_HEAP_DEGREE  2

typedef int HeapKeys;
typedef float HeapValues;

struct Heap {
  int Size;
  HeapKeys *Pos;
  HeapKeys *Node;
  HeapValues *key;
};

inline static Heap* HeapInit(HeapKeys maxitems) {
  Heap* h = (Heap*) malloc(sizeof(Heap));
  h->Node = (HeapKeys*) malloc(maxitems * sizeof(HeapKeys));
  h->Pos = (HeapKeys*) calloc(maxitems, sizeof(HeapKeys));
  h->Size = 0;
  return h;
}

inline static void HeapFree(Heap *h) {
  free(h->Node);
  free(h->Pos);
  free(h);
}

inline static void HeapSetKeys(Heap *h, HeapValues *k) {
  h->key = k;
}

inline static int HeapSize(Heap *h) {
  return h->Size;
}

inline static void PLACE_NODE(Heap* h, const HeapKeys& v, const HeapKeys& i) {
  h->Node[i] = (v);
  h->Pos[v] = (i);
}

inline static HeapKeys HeapMin(Heap *h) {
  return h->Node[0];
}

inline static void HeapDecKey(Heap *h, HeapKeys v) {
   HeapKeys iCurrent, iParent;
   HeapKeys nodeParent;
   HeapValues x;
   HeapValues *key = h->key;
   HeapKeys *Pos = h->Pos;
   HeapKeys *Node = h->Node;
   x=key[v];
   for (iCurrent = Pos[v], iParent = (Pos[v]-1) >> LOG_HEAP_DEGREE;
	iCurrent > 0;
	iCurrent = iParent, iParent = (iParent-1) >> LOG_HEAP_DEGREE ) {
      nodeParent = Node[iParent];
      if ( x >= key[nodeParent] )   /* we are in the right place*/
	 break;
      PLACE_NODE(h, nodeParent, iCurrent);     /* else move the parent down*/
   }
   PLACE_NODE(h, v, iCurrent );              /* put the node in the hole*/
}

inline static void HeapInsert(Heap *h, HeapKeys v) {
  PLACE_NODE(h, v, h->Size);
  h->Size++;
  HeapDecKey(h, v);
}

inline static HeapKeys Min(const HeapKeys& a, const HeapKeys& b) {
  return a < b ? a : b;
}

inline static void HeapDelMin(Heap *h) {
   HeapKeys iCurrent, iChild, iGoodChild, iFirstChild, iLastChild;
   HeapValues minValue;      /* min value of children of us (dbl for prec.)*/
   HeapKeys node;
   HeapValues nodekey;
   HeapValues *key = h->key;
   HeapKeys *Node = h->Node;
   h->Size--;
   node=Node[h->Size];
   nodekey=key[node];
   for ( iCurrent = 0;
	 /* break when value <= min */;
	 iCurrent = iGoodChild ) {
      iFirstChild = (iCurrent << LOG_HEAP_DEGREE) + 1;
      iLastChild = Min( iFirstChild + (1 << LOG_HEAP_DEGREE) - 1, h->Size - 1 );
      if ( iFirstChild >= h->Size )                 /* at the end of the tree*/
	 break;
      minValue = key[Node[iFirstChild]];
      iGoodChild = iFirstChild;                  /* the child with the min*/
      for (iChild = iFirstChild+1; iChild <= iLastChild; iChild++ )
	if ( key[Node[iChild]] < minValue ) {   /* new min*/
          minValue = key[Node[iChild]];
	  iGoodChild = iChild;
	}
      if ( nodekey <= minValue )             /* no need to move down-er*/
	 break;
      PLACE_NODE(h, Node[iGoodChild], iCurrent );
   }                                             /* end for*/
   PLACE_NODE(h, node, iCurrent );                /* Node goes in hole*/
}

inline static void HeapPrint(Heap *h) {
   HeapKeys iNode, iChild;
   HeapValues *key = h->key;
   HeapKeys *Node = h->Node;
   int Size = h->Size;
   fprintf(stderr, "\nTHE HEAP: size %i", Size);
   for ( iNode = 0; iNode < Size; iNode++ ) {
      fprintf(stderr,"\npos %i (%i,%lf): ", (int)iNode, (int)Node[iNode], key[Node[iNode]]);
      for (iChild = (iNode << LOG_HEAP_DEGREE) + 1;
           iChild <= (iNode+1) << LOG_HEAP_DEGREE  &&  iChild < Size;
           iChild++ ) {
         fprintf(stderr, "(%i,%lf) ", (int)Node[iChild], key[Node[iChild]]);
         if ( key[Node[iChild]] < key[Node[iNode]] ) {
           fprintf(stderr, "** bad bad bad **");
           exit(0);
         }
      }
   }
   fprintf(stderr, "\n\n");
}

#endif
