/*
 * Copyright (C) 2023
 * Author : Masatoshi Sasai ,MEGATRADE corporation
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */




#ifndef IMAGE_H_
#define IMAGE_H_

#include <stdio.h>
#include <stdint.h>
#include "XImagePngDef.h"
#include "XTypeDef.h"

#define COLOR_TYPE_INDEX 0   /**< �C���f�b�N�X�J���[���� */
#define COLOR_TYPE_GRAY  1   /**< �O���[�X�P�[������ */
#define COLOR_TYPE_RGB   2   /**< RGB���� */
#define COLOR_TYPE_RGBA  3   /**< RGBA���� */

/**
 * @brief �F����
 *
 * RGBA�̐F�������ێ������\����
 */

typedef struct color_t {
  uint8_t r; /**< Red */
  uint8_t g; /**< Green */
  uint8_t b; /**< Blue */
  uint8_t a; /**< Alpha */
} color_t;

/**
 * @brief ���f����
 *
 * ���p�̂ɂȂ��Ă����A
 * RGBA�l�A�O���[�X�P�[���A�J���[�C���f�b�N�X�A�̂����ꂩ���\�������B
 * �P�̂ł͂ǂ̕\���`���ɂȂ��Ă��邩�𔻒f���邱�Ƃ͂ł��Ȃ��B
 */

typedef union pixcel_t {
  color_t c; /**< RGBA */
  uint8_t g; /**< �O���[�X�P�[�� */
  uint8_t i; /**< �J���[�C���f�b�N�X */
} pixcel_t;

/**
 * @brief �摜�f�[�^�ێ��̍\����
 *
 * �摜�f�[�^�Ƃ��ĕێ����邽�߂ɕK�v�ŏ����̏������i�[�����B
 * �e�탁�^�f�[�^�̕ێ��ɂ��Ă͍����̉ۑ��B
 *
 * ���f�����ɂ��ẮA�|�C���^�̃|�C���^�ŕ\�����Ă���
 * �e�s�ւ̃|�C���^���ێ������z���ւ̃|�C���^�ƂȂ��Ă����B
 */

typedef struct image_t {
  uint32_t width;       /**< �� */
  uint32_t height;      /**< ���� */
  uint16_t color_type;  /**< �F�\���̎��� */
  uint16_t palette_num; /**< �J���[�p���b�g�̐� */
  color_t *palette;     /**< �J���[�p���b�g�ւ̃|�C���^ */
  pixcel_t **map;       /**< �摜�f�[�^ */
} image_t;



void dump_image_info(image_t *img);
image_t *allocate_image(uint32_t width, uint32_t height, uint8_t type);
image_t *clone_image(image_t *img);
void free_image(image_t *img);
color_t color_from_rgb(uint8_t r, uint8_t g, uint8_t b);
color_t color_from_rgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
image_t *image_to_index(image_t *img);
image_t *image_to_gray(image_t *img);
image_t *image_to_rgb(image_t *img);
image_t *image_to_rgba(image_t *img);
image_t *image_index_to_rgb(image_t *img);
image_t *image_rgb_to_index(image_t *img);
image_t *image_gray_to_index(image_t *img);
image_t *image_rgba_to_rgb(image_t *img, color_t bg);
image_t *image_rgba_to_rgb_ignore_alpha(image_t *img);
image_t *image_gray_to_rgb(image_t *img);
image_t *image_rgb_to_gray(image_t *img);
image_t *image_gray_to_binary(image_t *img);

/* PNG�`���̓ǂݏ��� */
image_t *read_png_file(const char *filename);
image_t *read_png_stream(FILE *fp);
result_t write_png_file(const char *filename, image_t *img);
result_t write_png_stream(FILE *fp, image_t *img);

/* JPG�`���̓ǂݏ��� */
image_t *read_jpeg_file(const char *filename);
image_t *read_jpeg_stream(FILE *fp);
result_t write_jpeg_file(const char *filename, image_t *img);
result_t write_jpeg_stream(FILE *fp, image_t *img);

/* BMP�`���̓ǂݏ��� */
image_t *read_bmp_file(const char *filename);
image_t *read_bmp_stream(FILE *fp);
result_t write_bmp_file(const char *filename, image_t *img, int compress);
result_t write_bmp_stream(FILE *fp, image_t *img, int compress);

image_t *read_bmp_simple_file(const char *filename);
image_t *read_bmp_simple_stream(FILE *fp);
result_t write_bmp_simple_file(const char *filename, image_t *img);
result_t write_bmp_simple_stream(FILE *fp, image_t *img);

/* PNM(PPM/PGM/PBM)�`���̓ǂݏ��� */
image_t *read_pnm_file(const char *filename);
image_t *read_pnm_stream(FILE *fp);
result_t write_pnm_file(const char *filename, image_t *img, int type);
result_t write_pnm_stream(FILE *fp, image_t *img, int type);

#endif /* IMAGE_H_ */