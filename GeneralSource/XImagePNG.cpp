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

#include "XTypeDef.h"
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include "XImagePNG.h"


void dump_image_info(image_t *img) {

  fprintf(stderr, "width:  %u\n", img->width);
  fprintf(stderr, "height: %u\n", img->height);
  fprintf(stderr, "type:   %d\n", img->color_type);
  fprintf(stderr, "pnum:   %d\n", img->palette_num);
  fprintf(stderr, "palette:%p\n", img->palette);

#if 0

  if (img->palette_num != 0) {

    int i;

    for (i = 0; i < img->palette_num; i++) {

      color_t *p = &img->palette[i];

      fprintf(stderr, "%3d: r:%02X g:%02X b:%02X\n", i, p->r, p->g, p->b);

    }

  }

#endif

}



/**
 * @brief image_t�^�\���̂̃��������m�ۂ������������B
 *
 * @param[in] width   �摜�̕�
 * @param[in] height  �摜�̍���
 * @param[in] type    �F�\���̎���
 * @return �������ς�image_t�^�\����
 */

image_t *allocate_image(uint32_t width, uint32_t height, uint8_t type) {

  uint32_t i;
  image_t *img;
  if ((img = (image_t *)calloc(1, sizeof(image_t))) == NULL) {
    return NULL;
  }

  img->width = width;
  img->height = height;
  img->color_type = type;
  if (type == COLOR_TYPE_INDEX) {
    if ((img->palette = (color_t *)calloc(256, sizeof(color_t))) == NULL) {
      goto error;
    }
  } else {
    img->palette = NULL;
  }
  img->palette_num = 0;
  if ((img->map = (pixcel_t **)calloc(height, sizeof(pixcel_t*))) == NULL) {
    goto error;
  }
  for (i = 0; i < height; i++) {
    if ((img->map[i] = (pixcel_t *)calloc(width, sizeof(pixcel_t))) == NULL) {
      goto error;
    }
  }

  return img;

  error:
  free_image(img);
  return NULL;
}



/**
 * @brief image_t�^�̃N���[�����쐬�����B
 *
 * �J���[�p���b�g���C���[�W�f�[�^�͓����I�ɕʂɃ��������m�ۂ��Ă��邽�߁A
 * allocate��������memcpy���Ă��N���[���͍쐬�ł��Ȃ��B
 * ���̊֐����g����deepcopy���s�����ƁB
 *
 * @param[in] img �N���[����image_t�^�\����
 * @return �N���[�����ꂽimage_t�^�\����
 */

image_t *clone_image(image_t *img) {

  uint32_t i;
  image_t *new_img = allocate_image(img->width, img->height, img->color_type);
  if (new_img == NULL) {
    return NULL;
  }
  new_img->palette_num = img->palette_num;
  if (img->color_type == COLOR_TYPE_INDEX) {
    memcpy(new_img->palette, img->palette, sizeof(color_t) * img->palette_num);
  }
  for (i = 0; i < img->height; i++) {
    memcpy(new_img->map[i], img->map[i], sizeof(pixcel_t) * img->width);
  }
  return new_img;
}



/**
 * @brief image_t�^�\���̂̃��������J�������B
 *
 * �����I�Ɋm�ۂ������������J�������B
 * ���������o�[�̃|�C���^�𒼐ڕύX�����ꍇ
 * �����ɓ��삵�Ȃ����ߒ��ӁB
 *
 * @param[in,out] img �J������image_t�^�\����
 */

void free_image(image_t *img) {

  uint32_t i;

  if (img == NULL) {
    return;
  }
  if (img->palette != NULL) {
    free(img->palette);
  }
  for (i = 0; i < img->height; i++) {
    free(img->map[i]);
  }
  free(img->map);
  free(img);
}



/**
 * @brief RGB�l���w�肵��color_t�^�̒l���쐬�����B
 *
 * �A���t�@�l��0xff���ݒ肳�����B
 *
 * @param[in] r red
 * @param[in] g green
 * @param[in] b blue
 * @return color_t
 */

color_t color_from_rgb(uint8_t r, uint8_t g, uint8_t b) {

  color_t c;
  c.r = r;
  c.g = g;
  c.b = b;
  c.a = 0xff;

  return c;
}



/**
 * @brief RGBA�l���w�肵��color_t�^�̒l���쐬�����B
 *
 * @param[in] r red
 * @param[in] g green
 * @param[in] b blue
 * @param[in] a alpha
 * @return color_t
 */

color_t color_from_rgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {

  color_t c;

  c.r = r;
  c.g = g;
  c.b = b;
  c.a = a;

  return c;
}



/**
 * @brief �����̉摜���C���f�b�N�X�J���[�����ɕϊ������B
 *
 * ���F�ς݂̉摜�łȂ����Ύ��s��NULL���Ԃ��B
 *
 * �w��������image_t�^�̓����\�������������Ė߂����߁A
 * �����Ɏw�肵���|�C���^�ƁA�������̖߂��l�͓����l�ƂȂ�
 * ����image_t�^�͕ێ������Ȃ����߁A
 * �K�v�������Η\�߃N���[�����쐬���Ă����B
 *
 * @param[in,out] img �ϊ�����image_t�^�ւ̃|�C���^
 * @return �ϊ��ɐ��������ꍇ�A�����Ɏw�肳�ꂽ�|�C���^�A���s�����ꍇNULL���Ԃ��B
 */

image_t *image_to_index(image_t *img) {

  switch (img->color_type) {
    case COLOR_TYPE_INDEX:
      break;
    case COLOR_TYPE_GRAY:
      img = image_gray_to_index(img);
      break;
    case COLOR_TYPE_RGB:
      img = image_rgb_to_index(img);
      break;
    case COLOR_TYPE_RGBA:
      img = image_rgba_to_rgb(img, color_from_rgb(255, 255, 255));
      img = image_rgb_to_index(img);
      break;
  }
  return img;
}



/**
 * @brief �����̉摜��RGB�����ɕϊ������B
 *
 * RGBA�`���̏ꍇ�́A���w�i�ɕϊ������B
 * �w�i�F���w�肵�����ꍇ��
 * image_rgba_to_rgb()
 * �𗘗p���邱�ƁB
 *
 * �w��������image_t�^�̓����\�������������Ė߂����߁A
 * �����Ɏw�肵���|�C���^�ƁA�������̖߂��l�͓����l�ƂȂ��B
 * ����image_t�^�͕ێ������Ȃ����߁A
 * �K�v�������Η\�߃N���[�����쐬���Ă����B
 *
 * @param[in,out] img �ϊ�����image_t�^�ւ̃|�C���^
 * @return �ϊ��ɐ��������ꍇ�A�����Ɏw�肳�ꂽ�|�C���^�A���s�����ꍇNULL���Ԃ��B
 */

image_t *image_to_gray(image_t *img) {

  switch (img->color_type) {
    case COLOR_TYPE_INDEX:
      img = image_index_to_rgb(img);
      img = image_rgb_to_gray(img);
      break;
    case COLOR_TYPE_GRAY:
      break;
    case COLOR_TYPE_RGB:
      img = image_rgb_to_gray(img);
      break;
    case COLOR_TYPE_RGBA:
      img = image_rgba_to_rgb(img, color_from_rgb(255, 255, 255));
      img = image_rgb_to_gray(img);
      break;
  }
  return img;
}


/**
 * @brief �����̉摜��RGB�����ɕϊ������B
 *
 * RGBA�`���̏ꍇ�́A���w�i�ɕϊ������B
 * �w�i�F���w�肵�����ꍇ��
 * image_rgba_to_rgb()
 * �𗘗p���邱�ƁB
 *
 * �w��������image_t�^�̓����\�������������Ė߂����߁A
 * �����Ɏw�肵���|�C���^�ƁA�������̖߂��l�͓����l�ƂȂ��B
 * ����image_t�^�͕ێ������Ȃ����߁A
 * �K�v�������Η\�߃N���[�����쐬���Ă����B
 *
 * @param[in,out] img �ϊ�����image_t�^�ւ̃|�C���^
 * @return �ϊ��ɐ��������ꍇ�A�����Ɏw�肳�ꂽ�|�C���^�A���s�����ꍇNULL���Ԃ��B
 */

image_t *image_to_rgb(image_t *img) {

  switch (img->color_type) {
    case COLOR_TYPE_INDEX:
      img = image_index_to_rgb(img);
      break;
    case COLOR_TYPE_GRAY:
      img = image_gray_to_rgb(img);
      break;
    case COLOR_TYPE_RGB:
      break;
    case COLOR_TYPE_RGBA:
      img = image_rgba_to_rgb(img, color_from_rgb(255, 255, 255));
      break;
  }

  return img;
}



/**
 * @brief �����̉摜��RGBA�����ɕϊ������B
 *
 * RGB�`���Ƃ̈Ⴂ��Alpha�l�����邩�A�ۂ��Ȃ̂�
 * RGB�`���ɕϊ�������color_type��RGBA�ɕϊ������B
 *
 * �w��������image_t�^�̓����\�������������Ė߂����߁A
 * �����Ɏw�肵���|�C���^�ƁA�������̖߂��l�͓����l�ƂȂ��B
 * ����image_t�^�͕ێ������Ȃ����߁A
 * �K�v�������Η\�߃N���[�����쐬���Ă����B
 *
 * @param[in,out] img �ϊ�����image_t�^�ւ̃|�C���^
 * @return �ϊ��ɐ��������ꍇ�A�����Ɏw�肳�ꂽ�|�C���^�A���s�����ꍇNULL���Ԃ��B
 */

image_t *image_to_rgba(image_t *img) {

  switch (img->color_type) {
    case COLOR_TYPE_INDEX:
      img = image_index_to_rgb(img);
      img->color_type = COLOR_TYPE_RGBA;
      break;
    case COLOR_TYPE_GRAY:
      img = image_gray_to_rgb(img);
      img->color_type = COLOR_TYPE_RGBA;
      break;
    case COLOR_TYPE_RGB:
      img->color_type = COLOR_TYPE_RGBA;
      break;
    case COLOR_TYPE_RGBA:
      break;
  }
  return img;
}


/**
 * @brief �C���f�b�N�X�J���[��������RGB�����֕ϊ������B
 *
 * �w��������image_t�^�̓����\�������������Ė߂����߁A
 * �����Ɏw�肵���|�C���^�ƁA�������̖߂��l�͓����l�ƂȂ��B
 * ����image_t�^�͕ێ������Ȃ����߁A
 * �K�v�������Η\�߃N���[�����쐬���Ă����B
 *
 * @param[in,out] img �ϊ�����image_t�^�ւ̃|�C���^
 * @return �ϊ��ɐ��������ꍇ�A�����Ɏw�肳�ꂽ�|�C���^�A���s�����ꍇNULL���Ԃ��B
 */

image_t *image_index_to_rgb(image_t *img) {

  uint32_t x, y;

  if (img == NULL) {
    return NULL;
  }
  if (img->color_type != COLOR_TYPE_INDEX) {
    return NULL;
  }
  for (y = 0; y < img->height; y++) {
    for (x = 0; x < img->width; x++) {
      pixcel_t *p = &img->map[y][x];
      if (p->i >= img->palette_num) {
        return NULL;
      }
      p->c = img->palette[p->i];
    }
  }
  img->color_type = COLOR_TYPE_RGB;
  free(img->palette);
  img->palette = NULL;
  img->palette_num = 0;
  return img;
}

/**
 * @brief RGB���������C���f�b�N�X�J���[�����ɕϊ������B
 *
 * �F���̃J�E���g���s���A256�F�ȏ��g�p�����Ă����ꍇ�͎��s�����B
 * �\�ߌ��F�ς݂̉摜���n�����ƁB
 *
 * �w��������image_t�^�̓����\�������������Ė߂����߁A
 * �����Ɏw�肵���|�C���^�ƁA�������̖߂��l�͓����l�ƂȂ��B
 * ����image_t�^�͕ێ������Ȃ����߁A
 * �K�v�������Η\�߃N���[�����쐬���Ă����B
 *
 * @param[in,out] img �ϊ�����image_t�^�ւ̃|�C���^
 * @return �ϊ��ɐ��������ꍇ�A�����Ɏw�肳�ꂽ�|�C���^�A���s�����ꍇNULL���Ԃ��B
 */

image_t *image_rgb_to_index(image_t *img) {

  uint32_t i, x, y;

  int num = 0;
  color_t *palette;
  if (img == NULL) {
    return NULL;
  }

  if (img->color_type != COLOR_TYPE_RGB) {
    return NULL;
  }

  // �F�����J�E���g�����ƂƂ��ɃJ���[�p���b�g���쐬
  palette = (color_t *)calloc(256, sizeof(color_t));
  for (y = 0; y < img->height; y++) {
    for (x = 0; x < img->width; x++) {
      color_t *c = &img->map[y][x].c;
      for (i = 0; i < num; i++) {
        if (memcmp(c, &palette[i], sizeof(color_t)) == 0) {
          break;
        }
      }
      if (i == num) {
        // �p���b�g�ɂȂ��F
        if (num == 256) {
          // �F����256�F�ȏ゠���ƃp���b�g�`���ɂ͂ł��Ȃ�
          free(palette);
          return NULL;
        }
        // �p���b�g�ɒǉ�
        palette[i] = *c;
        num++;
      }
    }
  }
  // �J���[�p���b�g���쐬�ł����̂ŁA
  // �e�s�N�Z�����J���[�p���b�g�̃C���f�b�N�X�ɒu��
  for (y = 0; y < img->height; y++) {
    for (x = 0; x < img->width; x++) {
      pixcel_t *p = &img->map[y][x];
      color_t *c = &p->c;
      for (i = 0; i < num; i++) {
        if (memcmp(c, &palette[i], sizeof(color_t)) == 0) {
          break;
        }
      }
      memset(p, 0, sizeof(pixcel_t));
      p->i = i;
    }
  }
  img->color_type = COLOR_TYPE_INDEX;
  img->palette_num = num;
  img->palette = palette;
  return img;
}

/**
 * @brief �O���[�X�P�[�����������C���f�b�N�X�J���[�����ɕϊ������B
 *
 * �w��������image_t�^�̓����\�������������Ė߂����߁A
 * �����Ɏw�肵���|�C���^�ƁA�������̖߂��l�͓����l�ƂȂ��B
 * ����image_t�^�͕ێ������Ȃ����߁A
 * �K�v�������Η\�߃N���[�����쐬���Ă����B
 *
 * @param[in,out] img �ϊ�����image_t�^�ւ̃|�C���^
 * @return �ϊ��ɐ��������ꍇ�A�����Ɏw�肳�ꂽ�|�C���^�A���s�����ꍇNULL���Ԃ��B
 */

image_t *image_gray_to_index(image_t *img) {

  uint32_t i, x, y;
  color_t *palette;

  if (img == NULL) {
    return NULL;
  }
  if (img->color_type != COLOR_TYPE_GRAY) {
    return NULL;
  }
  // �O���C�X�P�[���̒l�����̂܂܃C���f�b�N�X�l�ɂȂ��悤�ɃJ���[�p���b�g���쐬
  palette = (color_t *)calloc(256, sizeof(color_t));
  for (i = 0; i < 256; i++) {
    palette[i].r = i;
    palette[i].g = i;
    palette[i].b = i;
    palette[i].a = 0xff;
  }
  // �J���[�p���b�g���쐬�ł����̂ŁA
  // �e�s�N�Z�����J���[�p���b�g�̃C���f�b�N�X�ɒu��
  for (y = 0; y < img->height; y++) {
    for (x = 0; x < img->width; x++) {
      pixcel_t *p = &img->map[y][x];
      uint8_t g = p->g;
      memset(p, 0, sizeof(pixcel_t));
      p->i = g;
    }
  }
  img->color_type = COLOR_TYPE_INDEX;
  img->palette_num = 256;
  img->palette = palette;
  return img;
}

/**
 * @brief RGBA��������RGB�����ɕϊ������B
 *
 * �w�肵���w�i�F�ɃA���t�@�u�����h�������ʂ�RGB�l�ɕϊ������B
 * �w�i�F�̃A���t�@�l�͖��������A0xff�̃A���t�@�l�������̂Ƃ��Ĉ��������B
 *
 * �w��������image_t�^�̓����\�������������Ė߂����߁A
 * �����Ɏw�肵���|�C���^�ƁA�������̖߂��l�͓����l�ƂȂ��B
 * ����image_t�^�͕ێ������Ȃ����߁A
 * �K�v�������Η\�߃N���[�����쐬���Ă����B
 *
 * @param[in,out] img �ϊ�����image_t�^�ւ̃|�C���^
 * @param[in] bg �A���t�@�u�����h���s���w�i�F
 * @return �ϊ��ɐ��������ꍇ�A�����Ɏw�肳�ꂽ�|�C���^�A���s�����ꍇNULL���Ԃ��B
 */

image_t *image_rgba_to_rgb(image_t *img, color_t bg) {

  uint32_t x, y;

  if (img == NULL) {
    return NULL;
  }
  if (img->color_type != COLOR_TYPE_RGBA) {
    return NULL;
  }
  for (y = 0; y < img->height; y++) {
    for (x = 0; x < img->width; x++) {
      pixcel_t *p = &img->map[y][x];
      const uint8_t a = p->c.a;
      p->c.r = (p->c.r * a + bg.r * (0xff - a) + 0x7f) / 0xff;
      p->c.g = (p->c.g * a + bg.g * (0xff - a) + 0x7f) / 0xff;
      p->c.b = (p->c.b * a + bg.b * (0xff - a) + 0x7f) / 0xff;
      p->c.a = 0xff;
    }
  }
  img->color_type = COLOR_TYPE_RGB;
  return img;
}

/**
 * @brief RGBA��������RGB�����ɕϊ������B
 *
 * �A���t�@�u�����h�͍s�킸�A
 * �P�ɃA���t�@�l�𖳎����ĕs���������邱�Ƃ�RGB�֕ϊ������B
 * �A���t�@�u�����h���s���Ȃ����ߕs���R�ȕϊ��ƂȂ��B
 * �����p�ɍ쐬�B
 *
 * �w��������image_t�^�̓����\�������������Ė߂����߁A
 * �����Ɏw�肵���|�C���^�ƁA�������̖߂��l�͓����l�ƂȂ��B
 * ����image_t�^�͕ێ������Ȃ����߁A
 * �K�v�������Η\�߃N���[�����쐬���Ă����B
 *
 * @param[in,out] img �ϊ�����image_t�^�ւ̃|�C���^
 * @return �ϊ��ɐ��������ꍇ�A�����Ɏw�肳�ꂽ�|�C���^�A���s�����ꍇNULL���Ԃ��B
 */

image_t *image_rgba_to_rgb_ignore_alpha(image_t *img) {

  uint32_t x, y;

  if (img == NULL) {
    return NULL;
  }
  if (img->color_type != COLOR_TYPE_RGBA) {
    return NULL;
  }
  for (y = 0; y < img->height; y++) {
    for (x = 0; x < img->width; x++) {
      img->map[y][x].c.a = 0xff;
    }
  }
  img->color_type = COLOR_TYPE_RGB;
  return img;
}



/**
 * @brief �O���[�X�P�[����������RGB�����ɕϊ������B
 *
 * �w��������image_t�^�̓����\�������������Ė߂����߁A
 * �����Ɏw�肵���|�C���^�ƁA�������̖߂��l�͓����l�ƂȂ��B
 * ����image_t�^�͕ێ������Ȃ����߁A
 * �K�v�������Η\�߃N���[�����쐬���Ă����B
 *
 * @param[in,out] img �ϊ�����image_t�^�ւ̃|�C���^
 * @return �ϊ��ɐ��������ꍇ�A�����Ɏw�肳�ꂽ�|�C���^�A���s�����ꍇNULL���Ԃ��B
 */

image_t *image_gray_to_rgb(image_t *img) {

  uint32_t x, y;

  if (img == NULL) {
    return NULL;
  }
  if (img->color_type != COLOR_TYPE_GRAY) {
    return NULL;
  }
  for (y = 0; y < img->height; y++) {
    for (x = 0; x < img->width; x++) {
      pixcel_t *p = &img->map[y][x];
      const uint8_t g = p->g;
      p->c.r = g;
      p->c.g = g;
      p->c.b = g;
      p->c.a = 0xff;
    }
  }
  img->color_type = COLOR_TYPE_RGB;
  return img;
}

/**
 * @brief RGB���������O���[�X�P�[�������ɕϊ������B
 *
 * �w��������image_t�^�̓����\�������������Ė߂����߁A
 * �����Ɏw�肵���|�C���^�ƁA�������̖߂��l�͓����l�ƂȂ��B
 * ����image_t�^�͕ێ������Ȃ����߁A
 * �K�v�������Η\�߃N���[�����쐬���Ă����B
 *
 * @param[in,out] img �ϊ�����image_t�^�ւ̃|�C���^
 * @return �ϊ��ɐ��������ꍇ�A�����Ɏw�肳�ꂽ�|�C���^�A���s�����ꍇNULL���Ԃ��B
 */

image_t *image_rgb_to_gray(image_t *img) {

  uint32_t x, y;

  if (img == NULL) {
    return NULL;
  }
  if (img->color_type != COLOR_TYPE_RGB) {
    return NULL;
  }
  for (y = 0; y < img->height; y++) {
    for (x = 0; x < img->width; x++) {
      pixcel_t *p = &img->map[y][x];
      const uint8_t r = p->c.r;
      const uint8_t g = p->c.g;
      const uint8_t b = p->c.b;
      // ITU-R BT.601�K���̋P�x�v�Z�ŕϊ�����
      const uint8_t gray = (uint8_t) (0.299f * r + 0.587f * g + 0.114f * b + 0.5f);
      memset(p, 0, sizeof(pixcel_t));
      p->g = gray;
    }
  }
  img->color_type = COLOR_TYPE_GRAY;
  return img;
}

/**
 * @brief �O���[�X�P�[����������2�l���������ɕϊ������B
 *
 * pbm�`���o�͗p
 *
 * �w��������image_t�^�̓����\�������������Ė߂����߁A
 * �����Ɏw�肵���|�C���^�ƁA�������̖߂��l�͓����l�ƂȂ��B
 * ����image_t�^�͕ێ������Ȃ����߁A
 * �K�v�������Η\�߃N���[�����쐬���Ă����B
 *
 * @param[in,out] img �ϊ�����image_t�^�ւ̃|�C���^
 * @return �ϊ��ɐ��������ꍇ�A�����Ɏw�肳�ꂽ�|�C���^�A���s�����ꍇNULL���Ԃ��B
 */

image_t *image_gray_to_binary(image_t *img) {

  uint32_t x, y;

  if (img == NULL) {
    return NULL;
  }
  if (img->color_type != COLOR_TYPE_GRAY) {
    return NULL;
  }
  img->palette_num = 2;
  img->palette = (color_t *)calloc(256, sizeof(color_t));
  img->palette[0] = color_from_rgb(255, 255, 255);
  img->palette[1] = color_from_rgb(0, 0, 0);
  for (y = 0; y < img->height; y++) {
    for (x = 0; x < img->width; x++) {
      pixcel_t *p = &img->map[y][x];
      p->i = (p->g < 128 ? 1 : 0);
    }
  }
  img->color_type = COLOR_TYPE_INDEX;
  return img;
}