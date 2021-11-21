#ifndef COO2CSC_H
#define COO2CSC_H

#include <stdint.h>

void coo2csc(uint32_t* const row, /*!< CSC row start indices */
             uint32_t* const col,
             uint32_t* const values,           /*!< CSC column indices */
             uint32_t const* const row_coo,    /*!< COO row indices */
             uint32_t const* const col_coo,    /*!< COO column indices */
             uint32_t const* const values_coo, /*!< COO column indices */
             uint32_t const nnz,        /*!< Number of nonzero elements */
             uint32_t const n,          /*!< Number of rows/columns */
             uint32_t const isOneBased, /*!< Whether COO is 0- or 1-based */
             uint32_t const isPattern);
#endif