/*
 * dma.h
 *
 * Copyright (c) 2014 Jeremy Garff <jer @ jers.net>
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification, are permitted
 * provided that the following conditions are met:
 *
 *     1.  Redistributions of source code must retain the above copyright notice, this list of
 *         conditions and the following disclaimer.
 *     2.  Redistributions in binary form must reproduce the above copyright notice, this list
 *         of conditions and the following disclaimer in the documentation and/or other materials
 *         provided with the distribution.
 *     3.  Neither the name of the owner nor the names of its contributors may be used to endorse
 *         or promote products derived from this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
 * FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#ifndef __DMA_H__
#define __DMA_H__


/*
 * DMA Control Block in Main Memory
 *
 * Note: Must start at a 256 byte aligned address.
 *       Use corresponding register field definitions.
 */
typedef struct
{
    uint32_t ti;
    uint32_t source_ad;
    uint32_t dest_ad;
    uint32_t txfr_len;
    uint32_t stride;
    uint32_t nextconbk;
    uint32_t resvd_0x18[2];
} __attribute__((packed)) dma_cb_t;

/*
 * DMA register set
 */
typedef struct
{
    uint32_t cs;
#define RPI_DMA_CS_RESET                         (1 << 31)
#define RPI_DMA_CS_ABORT                         (1 << 30)
#define RPI_DMA_CS_DISDEBUG                      (1 << 29)
#define RPI_DMA_CS_WAIT_OUTSTANDING_WRITES       (1 << 28)
#define RPI_DMA_CS_PANIC_PRIORITY(val)           ((val & 0xf) << 20)                
#define RPI_DMA_CS_PRIORITY(val)                 ((val & 0xf) << 16)
#define RPI_DMA_CS_ERROR                         (1 << 8)
#define RPI_DMA_CS_WAITING_OUTSTANDING_WRITES    (1 << 6)
#define RPI_DMA_CS_DREQ_STOPS_DMA                (1 << 5)
#define RPI_DMA_CS_PAUSED                        (1 << 4)
#define RPI_DMA_CS_DREQ                          (1 << 3)
#define RPI_DMA_CS_INT                           (1 << 2)
#define RPI_DMA_CS_END                           (1 << 1)
#define RPI_DMA_CS_ACTIVE                        (1 << 0)
    uint32_t conblk_ad;
    uint32_t ti;
#define RPI_DMA_TI_NO_WIDE_BURSTS                (1 << 26)
#define RPI_DMA_TI_WAITS(val)                    ((val & 0x1f) << 21)
#define RPI_DMA_TI_PERMAP(val)                   ((val & 0x1f) << 16)
#define RPI_DMA_TI_BURST_LENGTH(val)             ((val & 0xf) << 12)
#define RPI_DMA_TI_SRC_IGNORE                    (1 << 11)
#define RPI_DMA_TI_SRC_DREQ                      (1 << 10)
#define RPI_DMA_TI_SRC_WIDTH                     (1 << 9)
#define RPI_DMA_TI_SRC_INC                       (1 << 8)
#define RPI_DMA_TI_DEST_IGNORE                   (1 << 7)
#define RPI_DMA_TI_DEST_DREQ                     (1 << 6)
#define RPI_DMA_TI_DEST_WIDTH                    (1 << 5)
#define RPI_DMA_TI_DEST_INC                      (1 << 4)
#define RPI_DMA_TI_WAIT_RESP                     (1 << 3)
#define RPI_DMA_TI_TDMODE                        (1 << 1)
#define RPI_DMA_TI_INTEN                         (1 << 0)
    uint32_t source_ad;
    uint32_t dest_ad;
    uint32_t txfr_len;
#define RPI_DMA_TXFR_LEN_YLENGTH(val)            ((val & 0xffff) << 16)
#define RPI_DMA_TXFR_LEN_XLENGTH(val)            ((val & 0xffff) << 0)
    uint32_t stride;
#define RPI_DMA_STRIDE_D_STRIDE(val)             ((val & 0xffff) << 16)
#define RPI_DMA_STRIDE_S_STRIDE(val)             ((val & 0xffff) << 0)
    uint32_t nextconbk;
    uint32_t debug;
} __attribute__((packed)) dma_t;


#ifndef RPI2
 #define DMA_BASE				 (0x3F000000)
#else
 #define DMA_BASE				 (0x20000000)
#endif //RPI2

#define DMA0                                     (0x7000|DMA_BASE)  // 0x7e007000
#define DMA1                                     (0x7100|DMA_BASE)
#define DMA2                                     (0x7200|DMA_BASE)
#define DMA3                                     (0x7300|DMA_BASE)
#define DMA4                                     (0x7400|DMA_BASE)
#define DMA5                                     (0x7500|DMA_BASE)
#define DMA6                                     (0x7600|DMA_BASE)
#define DMA7                                     (0x7700|DMA_BASE)
#define DMA8                                     (0x7800|DMA_BASE)
#define DMA9                                     (0x7900|DMA_BASE)
#define DMA10                                    (0x7a00|DMA_BASE)
#define DMA11                                    (0x7b00|DMA_BASE)
#define DMA12                                    (0x7c00|DMA_BASE)
#define DMA13                                    (0x7d00|DMA_BASE)
#define DMA14                                    (0x7e00|DMA_BASE)
#define DMA15                                    (0xe05000|DMA_BASE)


#define PAGE_SIZE                                (1 << 12)
#define PAGE_MASK                                (~(PAGE_SIZE - 1))
#define PAGE_OFFSET(page)                        (page & (PAGE_SIZE - 1))


typedef struct dma_page
{
    struct dma_page *next;
    struct dma_page *prev;
    void *addr;
} dma_page_t;


uint32_t dmanum_to_phys(int dmanum);

void dma_page_init(dma_page_t *page);
dma_page_t *dma_page_add(dma_page_t *head, void *addr);
void dma_page_remove(dma_page_t *page);
void dma_page_remove_all(dma_page_t *head);
dma_page_t *dma_page_next(dma_page_t *head, dma_page_t *page);

void *dma_alloc(dma_page_t *head, uint32_t size);
dma_cb_t *dma_desc_alloc(uint32_t descriptors);
void dma_page_free(void *buffer, const uint32_t size);


#endif /* __DMA_H__ */
