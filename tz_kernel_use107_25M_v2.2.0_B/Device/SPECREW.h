#ifndef __SPEC_REW_H__
#define __SPEC_REW_H__
const u8 atab[943] = { /* Register addresses */
    7, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
    6, 6, 6, 6, 6, 6, 6, 6, 6, 7, 6, 6, 6, 6, 6, 6,
    6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
    6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
    6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
    6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
    6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
    6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
    6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
    6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
    6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
    6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
    6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
    6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
    6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
    7, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
    6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
    6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
    6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
    6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
    6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
    6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
    6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
    6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
    6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
    6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
    6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
    6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
    6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
    6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
    6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
    6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
    6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
    6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
    6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
    6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
    6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
    6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
    6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
    6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
    6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
    6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
    6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
    6, 7, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
    6, 6, 6, 6, 6, 6, 6, 6, 6, 7, 6, 6, 6, 6, 6, 6,
    6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
    6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
    6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
    6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
    6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 7, 6,
    6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
    6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
    6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
    6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
    6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
    6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
    6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
    6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 7,
    6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 10
};
const u16 dtab[943] = { /* Data to write */
    0x8050, 0x3613, 0x0024, 0x3e00, 0x3801, 0x0000, 0x16d7, 0xf400,
    0x55c0, 0x0000, 0x0a17, 0xf400, 0x57c0, 0x0006, 0x5017, 0xb080,
    0x0024, 0x3f00, 0x0024, 0x2000, 0x0000, 0x36f0, 0x1801, 0x2800,
    0x31c0, 0x805c, 0x3e12, 0xb817, 0x3e12, 0x3815, 0x3e05, 0xb814,
    0x3615, 0x0024, 0x0000, 0x800a, 0x3e10, 0x3801, 0x0006, 0x0000,
    0x3e10, 0xb803, 0x0000, 0x0303, 0x3e11, 0x3805, 0x3e11, 0xb807,
    0x3e14, 0x3812, 0xb884, 0x130c, 0x3410, 0x4024, 0x4112, 0x10d0,
    0x4010, 0x008c, 0x4010, 0x0024, 0xf400, 0x4012, 0x3000, 0x3840,
    0x3009, 0x3801, 0x0000, 0x0041, 0xfe02, 0x0024, 0x2900, 0x8440,
    0x48b2, 0x0024, 0x36f3, 0x0844, 0x6306, 0x8845, 0xae3a, 0x8840,
    0xbf8e, 0x8b41, 0xac32, 0xa846, 0xffc8, 0xabc7, 0x3e01, 0x7800,
    0xf400, 0x4480, 0x6090, 0x0024, 0x6090, 0x0024, 0xf400, 0x4015,
    0x3009, 0x3446, 0x3009, 0x37c7, 0x3009, 0x1800, 0x3009, 0x3844,
    0x48b3, 0xe1e0, 0x4882, 0x4040, 0xfeca, 0x0024, 0x5ac2, 0x0024,
    0x5a52, 0x0024, 0x4cc2, 0x0024, 0x48ba, 0x4040, 0x4eea, 0x4801,
    0x4eca, 0x9800, 0xff80, 0x1bc1, 0xf1eb, 0xe3e2, 0xf1ea, 0x184c,
    0x4c8b, 0xe5e4, 0x48be, 0x9804, 0x488e, 0x41c6, 0xfe82, 0x0024,
    0x5a8e, 0x0024, 0x525e, 0x1b85, 0x4ffe, 0x0024, 0x48b6, 0x41c6,
    0x4dd6, 0x48c7, 0x4df6, 0x0024, 0xf1d6, 0x0024, 0xf1d6, 0x0024,
    0x4eda, 0x0024, 0x0000, 0x0fc3, 0x2900, 0x8440, 0x4e82, 0x0024,
    0x4084, 0x130c, 0x0006, 0x0100, 0x3440, 0x4024, 0x4010, 0x0024,
    0xf400, 0x4012, 0x3200, 0x4024, 0xb132, 0x0024, 0x4214, 0x0024,
    0xf224, 0x0024, 0x6230, 0x0024, 0x0001, 0x0001, 0x2800, 0x2b49,
    0x0000, 0x0024, 0xf400, 0x40c2, 0x3200, 0x0024, 0xff82, 0x0024,
    0x48b2, 0x0024, 0xb130, 0x0024, 0x6202, 0x0024, 0x003f, 0xf001,
    0x2800, 0x2e51, 0x0000, 0x1046, 0xfe64, 0x0024, 0x48be, 0x0024,
    0x2800, 0x2f40, 0x3a01, 0x8024, 0x3200, 0x0024, 0xb010, 0x0024,
    0xc020, 0x0024, 0x3a00, 0x0024, 0x36f4, 0x1812, 0x36f1, 0x9807,
    0x36f1, 0x1805, 0x36f0, 0x9803, 0x36f0, 0x1801, 0x3405, 0x9014,
    0x36f3, 0x0024, 0x36f2, 0x1815, 0x2000, 0x0000, 0x36f2, 0x9817,
    0x80c7, 0x3e12, 0xb817, 0x3e12, 0x3815, 0x3e05, 0xb814, 0x3625,
    0x0024, 0x0000, 0x800a, 0x3e10, 0x7802, 0x3e10, 0xf804, 0x3e11,
    0x7810, 0x3e14, 0x7813, 0x0006, 0x0051, 0x3e13, 0xf80e, 0x3e13,
    0x4024, 0x3009, 0x3840, 0x3009, 0x3852, 0x2919, 0x64c0, 0x0006,
    0x06d0, 0x3100, 0x5bd2, 0x0006, 0x55d1, 0x3009, 0x1800, 0x3009,
    0x0402, 0x6126, 0x0024, 0x0006, 0x00d1, 0x2800, 0x4d05, 0xb882,
    0x0024, 0x0006, 0x0011, 0x3009, 0x3850, 0x0006, 0x0010, 0x3009,
    0x3800, 0x291d, 0x5800, 0x0000, 0x1800, 0x0006, 0x0010, 0xb882,
    0x0024, 0x291d, 0x5b00, 0x0000, 0x1700, 0x0000, 0x0301, 0x3900,
    0x5bc0, 0x0006, 0x55d1, 0x3009, 0x1bd0, 0x3009, 0x0404, 0x0006,
    0x0051, 0x2800, 0x3d00, 0x3901, 0x0024, 0x4448, 0x0401, 0x4192,
    0x0024, 0x6498, 0x2401, 0x001f, 0x4001, 0x6412, 0x0024, 0x0006,
    0x0011, 0x2800, 0x3c51, 0x0000, 0x058e, 0x2400, 0x4c0e, 0x0000,
    0x0013, 0x0006, 0x0051, 0x0006, 0x1a03, 0x3100, 0x4024, 0xf212,
    0x44c4, 0x4346, 0x0024, 0xf400, 0x40d5, 0x3500, 0x8024, 0x612a,
    0x0024, 0x0000, 0x0024, 0x2800, 0x4c51, 0x0000, 0x0024, 0x3613,
    0x0024, 0x3100, 0x3800, 0x291d, 0x8000, 0xf200, 0x0024, 0x003f,
    0xfec2, 0x4082, 0x4411, 0x3113, 0x1bc0, 0xa122, 0x0024, 0x0000,
    0x2002, 0x6124, 0x2401, 0x0000, 0x1002, 0x2800, 0x4608, 0x0000,
    0x0024, 0x003f, 0xf802, 0x3100, 0x4024, 0xb124, 0x0024, 0x2800,
    0x4bc0, 0x3900, 0x8024, 0x6124, 0x0024, 0x0000, 0x0802, 0x2800,
    0x4848, 0x0000, 0x0024, 0x003f, 0xfe02, 0x3100, 0x4024, 0xb124,
    0x0024, 0x2800, 0x4bc0, 0x3900, 0x8024, 0x6124, 0x0024, 0x0000,
    0x0402, 0x2800, 0x4a88, 0x0000, 0x0024, 0x003f, 0xff02, 0x3100,
    0x4024, 0xb124, 0x0024, 0x2800, 0x4bc0, 0x3900, 0x8024, 0x6124,
    0x0401, 0x003f, 0xff82, 0x2800, 0x4bc8, 0xb124, 0x0024, 0x3900,
    0x8024, 0xb882, 0x8c4c, 0x3830, 0x4024, 0x0006, 0x0091, 0x3904,
    0xd84c, 0x0006, 0x00d1, 0x0000, 0x0013, 0x3100, 0x904c, 0x4202,
    0x9bcc, 0x39f0, 0x4024, 0x3100, 0x4024, 0x3c00, 0x4024, 0xf400,
    0x44c1, 0x34f0, 0x8024, 0x6126, 0x0024, 0x0006, 0x06d0, 0x2800,
    0x5dd8, 0x4294, 0x0024, 0x2400, 0x5d82, 0x0000, 0x0024, 0xf400,
    0x4411, 0x3123, 0x0024, 0x3100, 0x8024, 0x4202, 0x0024, 0x4182,
    0x2401, 0x0000, 0x2002, 0x2800, 0x5d89, 0x0000, 0x0024, 0x3013,
    0x184c, 0x30f0, 0x7852, 0x6124, 0xb850, 0x0006, 0x0001, 0x2800,
    0x5588, 0x4088, 0x44c2, 0x4224, 0x0024, 0x4122, 0x0024, 0x4122,
    0x0024, 0xf400, 0x4051, 0x2900, 0x7440, 0x0000, 0x56c8, 0x4224,
    0x0024, 0x4122, 0x0024, 0x4122, 0x0024, 0x2900, 0x69c0, 0xf400,
    0x4051, 0x0004, 0x0002, 0x3009, 0x1bd0, 0x3023, 0x1bd2, 0x30e0,
    0x4024, 0x6124, 0x0024, 0x0000, 0x4002, 0x2800, 0x5988, 0x0000,
    0x0024, 0x0000, 0x0001, 0x3820, 0x4024, 0x30e0, 0x4024, 0x6124,
    0x0001, 0x003f, 0xff42, 0x2800, 0x5d88, 0x4182, 0x0024, 0x0000,
    0x0024, 0x2800, 0x5d95, 0x0000, 0x0024, 0x3613, 0x0024, 0x3e14,
    0xc024, 0x2900, 0x1700, 0x3e14, 0x0024, 0x36e3, 0x008c, 0x30e0,
    0x4024, 0xfe22, 0x4411, 0x48b6, 0x048c, 0x3900, 0x8024, 0x3033,
    0x0c4c, 0x0006, 0x0011, 0x6892, 0x04c2, 0xa122, 0x0402, 0x6126,
    0x0024, 0x0006, 0x0093, 0x2800, 0x6701, 0x0000, 0x0024, 0xb882,
    0x184c, 0x3413, 0x3812, 0x0006, 0x00d2, 0x3a00, 0x5bd2, 0x3300,
    0x4024, 0x0000, 0x0013, 0x3c00, 0x4024, 0xf400, 0x44c1, 0x34f0,
    0x8024, 0x6126, 0x0024, 0x0006, 0x0111, 0x2800, 0x6718, 0x4294,
    0x0024, 0x2400, 0x66c2, 0x0000, 0x0024, 0x0003, 0xf001, 0x3101,
    0x0024, 0xb412, 0x0024, 0x0028, 0x0001, 0x2800, 0x66c5, 0x6144,
    0x0024, 0x0004, 0x0002, 0x2800, 0x6681, 0x4422, 0x0024, 0x0000,
    0x1002, 0x6422, 0x0024, 0x2800, 0x66c0, 0x3900, 0x4024, 0x3900,
    0x4024, 0x3113, 0x0c4c, 0x36f3, 0x4024, 0x36f3, 0xd80e, 0x36f4,
    0x5813, 0x36f1, 0x5810, 0x36f0, 0xd804, 0x36f0, 0x5802, 0x3405,
    0x9014, 0x36f3, 0x0024, 0x36f2, 0x1815, 0x2000, 0x0000, 0x36f2,
    0x9817, 0x1868, 0x0032, 0x004f, 0x007e, 0x00c8, 0x013d, 0x01f8,
    0x0320, 0x04f6, 0x07e0, 0x0c80, 0x13d8, 0x1f7f, 0x3200, 0x4f5f,
    0x61a8, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x81a7, 0x3e12, 0xb814, 0x0000, 0x800a, 0x3e10, 0x3801,
    0x3e10, 0xb803, 0x3e11, 0x7806, 0x3e11, 0xf813, 0x3e13, 0xf80e,
    0x3e13, 0x4024, 0x3e04, 0x7810, 0x449a, 0x0040, 0x0001, 0x0003,
    0x2800, 0x7304, 0x4036, 0x03c1, 0x0003, 0xffc2, 0xb326, 0x0024,
    0x0018, 0x0042, 0x4326, 0x4495, 0x4024, 0x40d2, 0x0000, 0x0180,
    0xa100, 0x4090, 0x0010, 0x0fc2, 0x4204, 0x0024, 0xbc82, 0x4091,
    0x459a, 0x0024, 0x0000, 0x0054, 0x2800, 0x7204, 0xbd86, 0x4093,
    0x2400, 0x71c5, 0xfe01, 0x5e0c, 0x5c43, 0x5f2d, 0x5e46, 0x020c,
    0x5c56, 0x8a0c, 0x5e53, 0x5e0c, 0x5c43, 0x5f2d, 0x5e46, 0x020c,
    0x5c56, 0x8a0c, 0x5e52, 0x0024, 0x4cb2, 0x4405, 0x0018, 0x0044,
    0x654a, 0x0024, 0x2800, 0x8000, 0x36f4, 0x5810, 0x81d1, 0x3e12,
    0xb814, 0x0000, 0x800a, 0x3e10, 0x3801, 0x3e10, 0xb803, 0x3e11,
    0x7806, 0x3e11, 0xf813, 0x3e13, 0xf80e, 0x3e13, 0x4024, 0x3e04,
    0x7810, 0x449a, 0x0040, 0x0000, 0x0803, 0x2800, 0x7ec4, 0x30f0,
    0x4024, 0x0fff, 0xfec2, 0xa020, 0x0024, 0x0fff, 0xff02, 0xa122,
    0x0024, 0x4036, 0x0024, 0x0000, 0x1fc2, 0xb326, 0x0024, 0x0010,
    0x4002, 0x4326, 0x4495, 0x4024, 0x40d2, 0x0000, 0x0180, 0xa100,
    0x4090, 0x0010, 0x0042, 0x4204, 0x0024, 0xbc82, 0x4091, 0x459a,
    0x0024, 0x0000, 0x0054, 0x2800, 0x7dc4, 0xbd86, 0x4093, 0x2400,
    0x7d85, 0xfe01, 0x5e0c, 0x5c43, 0x5f2d, 0x5e46, 0x0024, 0x5c56,
    0x0024, 0x5e53, 0x5e0c, 0x5c43, 0x5f2d, 0x5e46, 0x0024, 0x5c56,
    0x0024, 0x5e52, 0x0024, 0x4cb2, 0x4405, 0x0010, 0x4004, 0x654a,
    0x9810, 0x0000, 0x0144, 0xa54a, 0x1bd1, 0x0006, 0x0013, 0x3301,
    0xc444, 0x687e, 0x2005, 0xad76, 0x8445, 0x4ed6, 0x8784, 0x36f3,
    0x64c2, 0xac72, 0x8785, 0x4ec2, 0xa443, 0x3009, 0x2440, 0x3009,
    0x2741, 0x36f3, 0xd80e, 0x36f1, 0xd813, 0x36f1, 0x5806, 0x36f0,
    0x9803, 0x36f0, 0x1801, 0x2000, 0x0000, 0x36f2, 0x9814, 0x8211,
    0x4c82, 0x0024, 0x0000, 0x0024, 0x2000, 0x0005, 0xf5c2, 0x0024,
    0x0000, 0x0980, 0x2000, 0x0000, 0x6010, 0x0024, 0x0050
};
#endif
