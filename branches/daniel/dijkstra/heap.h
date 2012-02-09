#ifndef _HEAP_H
#define _HEAP_H

#include <stdlib.h>
#include <stdio.h>

typedef long heapindices; /* indices of keys */
typedef float heapvalues; /* key values */

typedef struct {
  heapindices N;
  heapindices Size;
  heapindices *Pos;
  heapindices *Node;
  heapvalues *key;
} Heap;

inline static Heap* HeapInit(heapindices maxitems) {
  Heap* h = (Heap*) malloc(sizeof(Heap));
  h->N=maxitems;
  h->Size = 0;
  h->Node=(heapindices*) malloc(maxitems * sizeof(heapindices));
  h->Pos=(heapindices*) calloc(maxitems, sizeof(heapindices));
  return h;
}

inline static void HeapFree(Heap *h) {
  free(h->Node);
  free(h->Pos);
  free(h);
}

inline static void HeapSetKeys(Heap *h, heapvalues *k) {
  h->key = k;
}

inline static heapindices HeapSize(Heap *h) {
  return h->Size;
}

#define LOG_HEAP_DEGREE  2

#define MIN(a,b)        ( (a) > (b) ? (b) : (a) )

#define PLACE_NODE(v, i)    \
{ Node[i] = (v);  Pos[v] = (i); }


inline static heapindices HeapMin(Heap *h) {
  return h->Node[0];
}

inline static void HeapPrint(Heap *h) {
   heapindices iNode, iChild;
   heapvalues *key = h->key;
   heapindices *Node = h->Node;
   int Size = h->Size;
   fprintf(stderr, "\nTHE HEAP: size %i of %i", (int)Size, (int)h->N);
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

inline static void HeapDecKey(Heap *h, heapindices v, int addedForCompatibility=0)
//void HeapDecKey(Heap *h, heapindices v)
{
   heapindices iCurrent, iParent;
   heapindices nodeParent;
   heapvalues x;
   heapvalues *key = h->key;
   heapindices *Pos = h->Pos;
   heapindices *Node = h->Node;
   x=key[v];
   for (iCurrent=Pos[v], iParent=(Pos[v]-1)>>LOG_HEAP_DEGREE;
	iCurrent > 0;
	iCurrent = iParent, iParent = (iParent-1) >> LOG_HEAP_DEGREE ) {
      nodeParent = Node[iParent];
      if ( x >= key[nodeParent] )   /* we are in the right place*/
	 break;
      PLACE_NODE( nodeParent, iCurrent);     /* else move the parent down*/
   }
   PLACE_NODE( v, iCurrent );              /* put the node in the hole*/
}

inline static void HeapInsert(Heap *h, heapindices v) {
  heapindices *Pos = h->Pos;
  heapindices *Node = h->Node;
  PLACE_NODE(v,h->Size);
  h->Size++;
  HeapDecKey(h, v);
}


inline static void HeapDelMin(Heap *h) {
   heapindices iCurrent, iChild, iGoodChild, iFirstChild, iLastChild;
   heapvalues minValue;      /* min value of children of us (dbl for prec.)*/
   heapindices node;
   heapvalues nodekey;
   heapvalues *key = h->key;
   heapindices *Pos = h->Pos;
   heapindices *Node = h->Node;

   h->Size--;
   node=Node[h->Size];
   nodekey=key[node];
   for ( iCurrent = 0;
	 /* break when value <= min */;
	 iCurrent = iGoodChild ) {
      iFirstChild = (iCurrent << LOG_HEAP_DEGREE) + 1;
      iLastChild = MIN( iFirstChild + (1<<LOG_HEAP_DEGREE) - 1, h->Size-1 );
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
      PLACE_NODE(Node[iGoodChild], iCurrent );
   }                                             /* end for*/
   PLACE_NODE(node, iCurrent );                /* Node goes in hole*/
}

#endif
