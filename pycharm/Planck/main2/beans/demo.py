void __fastcall sub_41B8E0()
{
  __int128 r_w_distance2; // xmm14
  __int128 v1; // xmm15
  const void *v2; // rdx
  const void *v3; // rsi
  signed __int64 Src_size_v4; // rdi
  unsigned __int64 v5; // rax
  char *v6; // rax
  char *v7; // r9
  size_t v8; // rbx
  unsigned __int64 v9; // rbp
  char *v10; // r9
  size_t v11; // rdi
  double v12; // xmm11_8
  int *robot_index_maybe; // rbp
  double v14; // xmm7_8
  double *robot_info; // r15
  double robot_speed2; // xmm0_8
  double robot_speed; // xmm15_8
  int cargo_type; // ecx
  __int64 robot_radius; // xmm1_8
  __int64 robot_quality; // xmm0_8
  char *v21; // rax
  double **v22; // rsi
  double *v23; // rbx
  double robot_worktable_distance2; // xmm0_8
  __int64 v25; // rcx
  char *v26; // r12
  char *v27; // rax
  char *v28; // r12
  int v29; // edi
  int v30; // ebp
  int v31; // er14
  int *v32; // rax
  double v33; // xmm0_8
  int v34; // ecx
  __int32 v35; // edx
  __m128i *v36; // rcx
  bool v37; // cc
  __m128i *v38; // r9
  __int32 v39; // eax
  const __m128i *v40; // r10
  __m128i *i; // rax
  __int32 v42; // edx
  unsigned int *final_result; // rbx
  unsigned int *v44; // rsi
  double *target_worktable_info; // rax
  int v46; // edx
  unsigned int v47; // ecx
  double target_worktable_pos_x; // xmm1_8
  double target_worktable_pos_y; // xmm0_8
  double robot_y; // xmm4_8
  double orientation_d_value; // xmm0_8
  double orientation_d_value_fabs; // xmm9_8
  double v53; // xmm10_8
  double *v54; // rdi
  double *v55; // rsi
  double v56; // xmm14_8
  double v57; // xmm8_8
  double x_maybe; // xmm7_8
  double y_maybe; // xmm8_8
  unsigned __int64 v60; // rbp
  int v61; // edi
  double *v62; // r12
  double v63; // xmm0_8
  double v64; // xmm10_8
  double *robot_info_2; // rsi
  double v66; // xmm1_8
  double v67; // xmm0_8
  double *v68; // r12
  double v69; // xmm0_8
  double v70; // xmm10_8
  double v71; // xmm1_8
  double v72; // xmm0_8
  double *v73; // r12
  double two_robot_distance2; // xmm0_8
  double two_robot_distance; // xmm10_8
  double v76; // xmm1_8
  double v77; // xmm0_8
  double *v78; // r12
  double robot_distance_3_0_2; // xmm0_8
  double robot_distance_3_0; // xmm10_8
  double v81; // xmm1_8
  double v82; // xmm0_8
  __int64 v83; // r8
  unsigned __int64 v84; // rax
  unsigned int *v85; // rsi
  __int64 robot_id; // rdx
  int *v87; // rax
  __int64 v88; // rax
  __m128i *v89; // rax
  const __m128i *v90; // rax
  unsigned __int64 v91; // rdx
  unsigned __int64 v92; // r8
  const __m128i *v93; // r9
  __m128i v94; // xmm0
  __int32 *v95; // rdx
  char *v96; // rax
  __int32 v97; // ecx
  __int32 v98; // ecx
  __int32 v99; // ecx
  __int32 v100; // edx
  int **v101; // [rsp+20h] [rbp-158h]
  int *v102; // [rsp+28h] [rbp-150h]
  int *m128i_i32; // [rsp+30h] [rbp-148h]
  __m128i *Block; // [rsp+38h] [rbp-140h]
  int v105; // [rsp+4Ch] [rbp-12Ch]
  void *v106[2]; // [rsp+50h] [rbp-128h] BYREF
  char *v107; // [rsp+60h] [rbp-118h]
  void *v108[2]; // [rsp+70h] [rbp-108h] BYREF
  size_t v109; // [rsp+80h] [rbp-F8h]

  v2 = *(&Src + 1);
  v3 = Src;
  Src_size_v4 = (_BYTE *)*(&Src + 1) - (_BYTE *)Src;
  *(_OWORD *)v106 = 0i64;                       // 将指针v103所指向的内存地址的前8个字节（64位）的值设置为0
  v107 = 0i64;
  v5 = 0xCF3CF3CF3CF3CF3Dui64 * (((_BYTE *)*(&Src + 1) - (_BYTE *)Src) >> 3);// 进行n*64位的数据填充，ui64表示无符号64位整数，>>3是为了8字节对齐
  if ( v5 )
  {
    if ( v5 > 109802048057794950i64 )
      init_dynamic_memory();
    v6 = (char *)dynamic_memory_allocation_with_exception_handling((_BYTE *)*(&Src + 1) - (_BYTE *)Src);
    v2 = *(&Src + 1);
    v3 = Src;
    v7 = v6;
    v8 = (_BYTE *)*(&Src + 1) - (_BYTE *)Src;
    v9 = 0xCF3CF3CF3CF3CF3Dui64 * (((_BYTE *)*(&Src + 1) - (_BYTE *)Src) >> 3);
  }
  else
  {
    v8 = (_BYTE *)*(&Src + 1) - (_BYTE *)Src;
    v9 = 0i64;
    v7 = 0i64;
  }
  v107 = &v7[Src_size_v4];
  *(__m128i *)v106 = _mm_unpacklo_epi64((__m128i)(unsigned __int64)v7, (__m128i)(unsigned __int64)v7);
  if ( v2 == v3 )
  {
    v109 = 0i64;
    v106[1] = &v7[v8];
    *(_OWORD *)v108 = 0i64;
    if ( !v9 )
    {
      v109 = v8;
      v11 = v8;
      v10 = 0i64;
      goto LABEL_9;
    }
    goto LABEL_6;
  }
  *(_OWORD *)v108 = 0i64;
  v109 = 0i64;
  v106[1] = (char *)memmove(v7, v3, v8) + v8;   // 从v3指向的内存块中复制v8字节大小(672字节)的数据到v7
  if ( v9 )
  {
LABEL_6:
    if ( v9 > 0x186186186186186i64 )
      init_dynamic_memory();                    // 动态分配内存空间
    v10 = (char *)dynamic_memory_allocation_with_exception_handling(v8);// 一直申请内存空间直到成功
    v3 = Src;
    v109 = (size_t)&v10[v8];                    // 将内存空间的末尾地址存储在v106变量中
    *(__m128i *)v108 = _mm_unpacklo_epi64((__m128i)(unsigned __int64)v10, (__m128i)(unsigned __int64)v10);// 是将指针v10的地址打包进一个128位__m128i类型的变量v105中
    v11 = (_BYTE *)*(&Src + 1) - (_BYTE *)Src;  // 注意，这里是指针的指针，v11是Src指向内存块的大小
    if ( *(&Src + 1) == Src )                   // 如果内存块的大小为0，则跳转到标签LABEL_9处进行处理，否则跳转到标签LABEL_8处进行操作。
      goto LABEL_9;
    goto LABEL_8;
  }
  v109 = v8;
  v11 = v8;
  v10 = 0i64;
LABEL_8:
  v10 = (char *)memmove(v10, v3, v11);
LABEL_9:
  v108[1] = &v10[v11];
  v105 = dword_4D2058;
  Block = (__m128i *)dynamic_memory_allocation_with_exception_handling(0x10ui64);
  v12 = 80003.0;
  m128i_i32 = Block[1].m128i_i32;               // 将Block[1]内存区域中的一个32位整数元素的值赋值给了m128i_i32变量，类型应该是有符号32位int类型
  Block->m128i_i64[0] = 0x100000000i64;
  Block->m128i_i64[1] = 0x300000002i64;
  while ( 1 )
  {
    if ( worktable_num > 0 )
      memset(dword_4D2080, 0, 4i64 * (unsigned int)(worktable_num - 1) + 4);// 将 dword_4D2080 这个变量指向的内存空间填充为 0，填充的字节数为 (worktable_num - 1) * 4 + 4
    robot_index_maybe = (int *)Block;
    v14 = 0.0;
    qword_4D2060 = 0i64;
    qword_4D2068 = 0i64;
    do
    {
      robot_info = (double *)((char *)Src + 168 * *robot_index_maybe);// robot_index_maybe
      robot_speed2 = robot_info[5] * robot_info[5] + robot_info[6] * robot_info[6];// v15[5]存放的是robot的vx，v15[6]是vy，v15是8字节的数组
      robot_speed = sqrt(robot_speed2);
      if ( robot_speed2 < 0.0 )                 // 进行异常处理
        calculate_sqrt(robot_speed2);
      cargo_type = *((_DWORD *)robot_info + 2); // 机器人携带物品类型
      robot_info[4] = robot_speed;              // robot_info后面的第32个字节存放的速度
      if ( cargo_type )
      {
        robot_radius = 0x3FE0F5C28F5C28F6i64;   // 机器人半径
        robot_quality = 0x4031A64381000134i64;  // 17.649467527867458
      }
      else
      {
        robot_radius = 0x3FDCCCCCCCCCCCCDi64;   // 机器人半径0.45
        robot_quality = 0x40297268121EA0DCi64;  // 12.723450247038663
      }
      *((_QWORD *)robot_info + 8) = robot_radius;// 填充半径信息
      *((_QWORD *)robot_info + 9) = robot_quality;// 填充质量信息
      robot_info[13] = 0.0;
      robot_info[14] = 0.0;
      robot_info[16] = 20000.0;
      robot_info[17] = 20000.0;
      *((_WORD *)robot_info + 60) = 0;
      v21 = (char *)&xmmword_4D2240 + 24 * cargo_type;// 可能访问某个数组成员
      *((_BYTE *)robot_info + 122) = 0;
      robot_info[18] = 0.0;
      v22 = *(double ***)v21;
      if ( *(_QWORD *)v21 == *((_QWORD *)v21 + 1) )
      {
        v33 = 20000.0;
        goto LABEL_43;
      }
      v102 = robot_index_maybe;
      v23 = *v22;
      v101 = (int **)*((_QWORD *)v21 + 1);
      if ( cargo_type )
      {
LABEL_19:
        if ( ((1 << cargo_type) & *((_DWORD *)v23 + 7)) != 0 || ((1 << cargo_type) & dword_4D2080[*(int *)v23]) != 0 )// *((_DWORD *)v23 + 7))是原材料格，若为0则代表啥也没有，*(int *)v23]为上一个工作台类型
          goto LABEL_29;                        // 若工作台需要这种原材料，或者上一个工作台产出的产品与这种类型的原材料相匹配
        robot_worktable_distance2 = (robot_info[12] - v23[2]) * (robot_info[12] - v23[2])
                                  + (robot_info[11] - v23[1]) * (robot_info[11] - v23[1]);
        *(double *)&r_w_distance2 = sqrt(robot_worktable_distance2);
        if ( robot_worktable_distance2 >= 0.0 )
        {
LABEL_22:
          v25 = *((int *)v23 + 1);
          v26 = (char *)&unk_4D5BC0 + 48 * v25;
          v27 = (char *)*((_QWORD *)v26 + 3);
          v28 = v26 + 8;
          if ( v27 == v28 )
          {
            v1 = r_w_distance2;
          }
          else
          {
            v29 = *((_DWORD *)v23 + 7);
            v30 = 0;
            v31 = dword_4A8F20[v25];
            do
            {
              v30 += v31 * ((v29 & (1 << *((_DWORD *)v27 + 8))) != 0);
              v27 = (char *)sub_49DE30((__int64)v27);
            }
            while ( v28 != v27 );
            *((_QWORD *)&v1 + 1) = *((_QWORD *)&r_w_distance2 + 1);
            *(double *)&v1 = *(double *)&r_w_distance2 - (double)v30;
          }
          *(double *)&v1 = fmax(*(double *)&v1, 0.1);
          goto LABEL_27;
        }
        v1 = r_w_distance2;
LABEL_38:
        calculate_sqrt(robot_worktable_distance2);
        r_w_distance2 = v1;
        if ( *((_DWORD *)robot_info + 2) )      // 根据机器人携带的物品类型判断是否进行跳转
          goto LABEL_22;
LABEL_27:
        if ( robot_info[16] > *(double *)&v1 )  // 取最短，放在robot_info[16]中
        {
          *((_QWORD *)robot_info + 16) = v1;
          *((_QWORD *)robot_info + 17) = r_w_distance2;
          *((_QWORD *)robot_info + 18) = v23;
        }
        goto LABEL_29;
      }
      while ( 1 )
      {

        if ( *((_BYTE *)v23 + 32)               // 判断产品格
          && *((int *)&qword_4D2220 + *((int *)v23 + 1)) > 0
          && (((1 << *(_DWORD *)v23) & *((_DWORD *)&qword_4D2060 + ((unsigned __int64)*(int *)v23 >> 5))) == 0
           || dword_4D2058 <= 0) )
        {
          robot_worktable_distance2 = (robot_info[12] - v23[2]) * (robot_info[12] - v23[2])// 这里是计算机器人和工作台之间的距离
                                    + (robot_info[11] - v23[1]) * (robot_info[11] - v23[1]);// v23[1]是第一个工作台的坐标，此时v23地址为4D2400
          *(double *)&v1 = sqrt(robot_worktable_distance2);
          if ( robot_worktable_distance2 >= 0.0 )
          {
            r_w_distance2 = v1;
            goto LABEL_27;
          }
          goto LABEL_38;
        }
LABEL_29:
        if ( v101 == (int **)++v22 )            // 检查是否循环完成
          break;
        cargo_type = *((_DWORD *)robot_info + 2);
        v23 = *v22;
        if ( cargo_type )
          goto LABEL_19;
      }
      v32 = (int *)*((_QWORD *)robot_info + 18);
      robot_index_maybe = v102;
      v33 = robot_info[16];
      if ( v32 )
      {
        v34 = *((_DWORD *)robot_info + 2);
        if ( v34 )
        {
          dword_4D2080[*v32] |= 1 << v34;
          *((_BYTE *)robot_info + 121) = 1;
        }
        else if ( frame_id <= 8850 )
        {
          v83 = v32[1];
          v84 = *v32;
          *((_BYTE *)robot_info + 120) = 1;
          --dword_4D2058;
          --*((_DWORD *)&qword_4D2220 + v83);
          *((_DWORD *)&qword_4D2060 + (v84 >> 5)) |= 1 << v84;
        }
      }
LABEL_43:
      v14 = v14 + v33;
      ++robot_index_maybe;
    }
    while ( m128i_i32 != robot_index_maybe );
    if ( fabs(v14 - v12) >= 0.01 && v12 > v14 )
    {
      copy_pointers_to_array((char **)v108, (char **)&Src);
      v12 = v14;
    }
    copy_pointers_to_array((char **)&Src, (char **)v106);
    v35 = Block->m128i_i32[2];
    v36 = (__m128i *)&Block->m128i_i8[12];
    v37 = v35 < Block->m128i_i32[3];
    dword_4D2058 = v105;
    v38 = (__m128i *)&Block->m128i_i8[8];
    if ( v37 )
    {
      v40 = (const __m128i *)&Block->m128i_i8[12];
      goto LABEL_144;
    }
    v39 = Block->m128i_i32[1];
    v40 = (const __m128i *)&Block->m128i_i8[4];
    if ( v39 < v35 )
    {
      v40 = (const __m128i *)&Block->m128i_i8[8];
      v35 = Block->m128i_i32[1];
      v38 = (__m128i *)&Block->m128i_i8[4];
      goto LABEL_144;
    }
    v35 = Block->m128i_i32[0];
    if ( Block->m128i_i32[0] >= v39 )
      break;
    v38 = Block;
LABEL_144:
    v89 = Block + 1;
    do
      v89 = (__m128i *)((char *)v89 - 4);
    while ( v89->m128i_i32[0] <= v35 );
    v38->m128i_i32[0] = v89->m128i_i32[0];
    v89->m128i_i32[0] = v35;
    if ( m128i_i32 != (int *)v40 && v40 < v36 )
    {
      v90 = v40;
      v91 = (unsigned __int64)((char *)&Block->m128i_u64[1] + 3 - (char *)v40) >> 3;
      v92 = v91 + 1;
      if ( (v40 >= (const __m128i *)m128i_i32 || (char *)v36 - 4 * v91 >= (char *)v40->m128i_i64 + 4 * v91 + 4)
        && (unsigned __int64)((char *)&Block->m128i_u64[1] + 3 - (char *)v40) > 0x17 )
      {
        v93 = Block;
        do
        {
          v94 = _mm_loadu_si128(v90);
          --v93;
          ++v90;
          v90[-1] = _mm_shuffle_epi32(_mm_loadu_si128(v93 + 1), 27);
          v93[1] = _mm_shuffle_epi32(v94, 27);
        }
        while ( &Block[-(v92 >> 2)] != v93 );
        v95 = &v40->m128i_i32[v92 & 0xFFFFFFFFFFFFFFFCui64];
        v96 = &v36->m128i_i8[-4 * (v92 & 0xFFFFFFFFFFFFFFFCui64)];
        if ( (v92 & 0xFFFFFFFFFFFFFFFCui64) != v92 )
        {
          v97 = *v95;
          *v95 = *(_DWORD *)v96;
          *(_DWORD *)v96 = v97;
          if ( v96 - 4 > (char *)v95 + 4 )
          {
            v98 = v95[1];
            v95[1] = *((_DWORD *)v96 - 1);
            *((_DWORD *)v96 - 1) = v98;
            if ( v96 - 8 > (char *)v95 + 8 )
            {
              v99 = v95[2];
              v95[2] = *((_DWORD *)v96 - 2);
              *((_DWORD *)v96 - 2) = v99;
            }
          }
        }
      }
      else
      {
        do
        {
          v100 = v90->m128i_i32[0];
          v36 = (__m128i *)((char *)v36 - 4);
          v90 = (const __m128i *)((char *)v90 + 4);
          v90[-1].m128i_i32[3] = v36->m128i_i32[1];
          v36->m128i_i32[1] = v100;
        }
        while ( v36 > v90 );
      }
    }
  }
  for ( i = Block; i < v36; v36->m128i_i32[1] = v42 )// i是指向输入数据块的指针，v36是一个指向输出数据块的指针
  {
    v42 = i->m128i_i32[0];                      // v42是一个临时变量，用于暂存输入数据块的第一个整数的值
    v36 = (__m128i *)((char *)v36 - 4);         // 移动指针
    i = (__m128i *)((char *)i + 4);             // 移动指针
    i[-1].m128i_i32[3] = v36->m128i_i32[1];
  }
  copy_pointers_to_array((char **)&Src, (char **)v108);// 指针数组v108中的指针所指向的内存区域复制到指针数组Src所指向的内存区域，并返回Src。
  v44 = (unsigned int *)*(&Src + 1);
  final_result = (unsigned int *)Src;
  if ( *(&Src + 1) != Src )
  {
    while ( 1 )
    {
      target_worktable_info = (double *)*((_QWORD *)final_result + 18);
      if ( !target_worktable_info )
        goto LABEL_55;
      v46 = *(_DWORD *)target_worktable_info;
      v47 = final_result[1];
      *((_BYTE *)final_result + 122) = v47 == *(_DWORD *)target_worktable_info;
      if ( v47 == v46 )
      {
        *((_QWORD *)final_result + 13) = 0i64;
        *((_QWORD *)final_result + 14) = 0i64;
LABEL_55:
        final_result += 42;
        if ( v44 == final_result )
          goto LABEL_68;
      }
      else
      {
        target_worktable_pos_x = target_worktable_info[1];// 目标工作台的x坐标
        target_worktable_pos_y = target_worktable_info[2];// 目标工作台的y坐标
        robot_y = *((double *)final_result + 12);
        if ( fabs(*((double *)final_result + 11) - target_worktable_pos_x) < 0.0000001
          && fabs(robot_y - target_worktable_pos_y) < 0.0000001 )
        {
          goto LABEL_113;
        }
        orientation_d_value = atan2_(
                                target_worktable_pos_y - robot_y,
                                target_worktable_pos_x - *((double *)final_result + 11))
                            - *((double *)final_result + 10);// 计算 atan2_() 函数的结果与 final_result 数组中第十个双精度浮点型变量的差值，并将计算结果存储到变量 v48 中
        if ( orientation_d_value > 3.141592653589793 )
        {
          orientation_d_value = orientation_d_value - 6.283185307179586;
        }
        else if ( orientation_d_value < -3.141592653589793 )
        {
          orientation_d_value = orientation_d_value + 6.283185307179586;
        }
        orientation_d_value_fabs = fabs(orientation_d_value);
        v53 = 3.454092653589793;
        if ( orientation_d_value <= 0.0 )
          v53 = -3.454092653589793;
        if ( orientation_d_value_fabs < 0.08 )  // !!!!!!若方向差值小于0.08就输出旋转为0
        {
LABEL_113:
          *((_QWORD *)final_result + 14) = 0i64;// 输出旋转为0
          *((_QWORD *)final_result + 13) = 0x4018000000000000i64;
          goto LABEL_55;
        }
        if ( orientation_d_value_fabs <= 1.570796326794897 )// 这个是当方向差小于π/2
        {
          *((double *)final_result + 13) = calculateCosine_(orientation_d_value) * 6.0;// 当方向差小于π/2，就计算速度
          *((double *)final_result + 14) = v53 * adjust_sine_(orientation_d_value_fabs);// 当方向差小于π/2，就特殊计算旋转角度
          goto LABEL_55;
        }
        *((double *)final_result + 14) = v53;   // 当方向差在0和π/2之间，就把旋转角度设置为v50
        final_result += 42;
        *((_QWORD *)final_result - 8) = 0x3FF3333333333334i64;
        if ( v44 == final_result )
        {
LABEL_68:
          v54 = (double *)*(&Src + 1);
          final_result = (unsigned int *)Src;
          if ( Src != *(&Src + 1) )
          {
            v55 = (double *)Src;
            do
            {
              v56 = v55[10];
              v57 = v55[4];
              x_maybe = calculateCosine_(v56) * v57 * 15.0 / 50.0 + v55[11];// v55[11]是机器人的x坐标
              v55[19] = x_maybe;
              y_maybe = v57 * adjust_sine_(v56) * 15.0 / 50.0 + v55[12];
              v55[20] = y_maybe;
              if ( x_maybe > 49.75 || y_maybe > 49.75 || x_maybe < 0.25 || y_maybe < 0.25 )// 边界判断，防止出界
                v55[13] = -v55[13];
              v55 += 21;
            }
            while ( v54 != v55 );
          }
          break;
        }
      }
    }
  }
  v60 = 0i64;
  v61 = 0;
  while ( 2 )
  {
    if ( !v61 )
    {
LABEL_86:
      v68 = (double *)&final_result[v60 / 4];
      v69 = (*((double *)final_result + 33) - *(double *)&final_result[v60 / 4 + 24])// final_result+33为1号机器人的y坐标
          * (*((double *)final_result + 33) - *(double *)&final_result[v60 / 4 + 24])
          + (*((double *)final_result + 32) - *(double *)&final_result[v60 / 4 + 22])
          * (*((double *)final_result + 32) - *(double *)&final_result[v60 / 4 + 22]);
      v70 = sqrt(v69);
      if ( v69 < 0.0 )
      {
        calculate_sqrt(v69);
        robot_info_2 = (double *)Src;
      }
      else
      {
        robot_info_2 = (double *)final_result;
      }
      if ( *((double *)final_result + 29) + v68[8] + 0.002 >= v70 )// v68[8]是0.45
      {
        v71 = v68[10];
        v72 = v68[14];
        if ( *((double *)final_result + 32) > v68[11] )
        {
          if ( v71 <= 0.0 )
            goto LABEL_91;
        }
        else if ( v71 > 0.0 )
        {
LABEL_91:
          v68[14] = v72 - 0.7675761452421762;
          goto LABEL_92;
        }
        v68[14] = v72 + 0.7675761452421762;
      }
LABEL_92:
      if ( v61 != 2 )
        goto LABEL_93;
      goto LABEL_100;
    }
    v62 = (double *)&final_result[v60 / 4];
    v63 = (*((double *)final_result + 11) - *(double *)&final_result[v60 / 4 + 22])
        * (*((double *)final_result + 11) - *(double *)&final_result[v60 / 4 + 22])
        + (*((double *)final_result + 12) - *(double *)&final_result[v60 / 4 + 24])
        * (*((double *)final_result + 12) - *(double *)&final_result[v60 / 4 + 24]);
    v64 = sqrt(v63);
    if ( v63 < 0.0 )
    {
      calculate_sqrt(v63);
      robot_info_2 = (double *)Src;
    }
    else
    {
      robot_info_2 = (double *)final_result;
    }
    if ( v62[8] + *((double *)final_result + 8) + 0.002 >= v64 )
    {
      v66 = v62[10];
      v67 = v62[14];
      if ( *((double *)final_result + 11) > v62[11] )
      {
        if ( v66 > 0.0 )
          goto LABEL_132;
LABEL_83:
        v62[14] = v67 - 0.7675761452421762;
      }
      else
      {
        if ( v66 > 0.0 )
          goto LABEL_83;
LABEL_132:
        v62[14] = v67 + 0.7675761452421762;
      }
    }
    if ( v61 != 1 )
    {
      final_result = (unsigned int *)robot_info_2;
      goto LABEL_86;
    }
LABEL_93:
    v73 = &robot_info_2[v60 / 8];
    two_robot_distance2 = (robot_info_2[54] - robot_info_2[v60 / 8 + 12])
                        * (robot_info_2[54] - robot_info_2[v60 / 8 + 12])// v65[53]:第2个机器人x，v65[54]:第2个机器人y
                        + (robot_info_2[53] - robot_info_2[v60 / 8 + 11])
                        * (robot_info_2[53] - robot_info_2[v60 / 8 + 11]);// v65[11]:第0个机器人x，v65[12]:第0个机器人y
    two_robot_distance = sqrt(two_robot_distance2);
    if ( two_robot_distance2 < 0.0 )
    {
      calculate_sqrt(two_robot_distance2);
      final_result = (unsigned int *)Src;
    }
    else
    {
      final_result = (unsigned int *)robot_info_2;
    }
    if ( robot_info_2[50] + v73[8] + 0.002 >= two_robot_distance )
    {
      v76 = v73[10];
      v77 = v73[14];
      if ( robot_info_2[53] > v73[11] )
      {
        if ( v76 > 0.0 )
          goto LABEL_115;
        v73[14] = v77 - 0.7675761452421762;
      }
      else
      {
        if ( v76 > 0.0 )
        {
          v73[14] = v77 - 0.7675761452421762;
          if ( v61 == 3 )
            goto LABEL_117;
LABEL_99:
          robot_info_2 = (double *)final_result;
LABEL_100:
          v78 = &robot_info_2[v60 / 8];
          robot_distance_3_0_2 = (robot_info_2[74] - robot_info_2[v60 / 8 + 11])
                               * (robot_info_2[74] - robot_info_2[v60 / 8 + 11])// robot_info_2[74]第3个机器人的x,robot_info_2[75]第3个机器人的y
                               + (robot_info_2[75] - robot_info_2[v60 / 8 + 12])
                               * (robot_info_2[75] - robot_info_2[v60 / 8 + 12]);// robot_info_2[11]第0个机器人的x,robot_info_2[12]第0个机器人的y
          robot_distance_3_0 = sqrt(robot_distance_3_0_2);
          if ( robot_distance_3_0_2 < 0.0 )
          {
            calculate_sqrt(robot_distance_3_0_2);
            final_result = (unsigned int *)Src;
          }
          else
          {
            final_result = (unsigned int *)robot_info_2;
          }
          if ( v78[8] + robot_info_2[71] + 0.002 >= robot_distance_3_0 )
          {
            v81 = v78[10];
            v82 = v78[14];
            if ( robot_info_2[74] <= v78[11] )
            {
              if ( v81 > 0.0 )
                goto LABEL_134;
LABEL_105:
              v78[14] = v82 + 0.7675761452421762;
            }
            else
            {
              if ( v81 > 0.0 )
                goto LABEL_105;
LABEL_134:
              v78[14] = v82 - 0.7675761452421762;
            }
          }
          ++v61;
          v60 += 168i64;
          if ( v61 == 4 )
            goto LABEL_117;
          continue;
        }
LABEL_115:
        v73[14] = v77 + 0.7675761452421762;
      }
    }
    break;
  }
  if ( v61 != 3 )
    goto LABEL_99;
LABEL_117:
  v85 = (unsigned int *)*(&Src + 1);
  if ( *(&Src + 1) != final_result )
  {
    do
    {
      robot_id = *final_result;
      if ( *((_BYTE *)final_result + 122) )
      {
        if ( *((_BYTE *)final_result + 121)
          && (sub_41CE10("sell %d\n", robot_id),
              v87 = (int *)*((_QWORD *)final_result + 18),
              robot_id = *final_result,
              *((_BYTE *)v87 + 32))
          && frame_id <= 8850                   // 在8850帧内就允许买
          && *((int *)&qword_4D2220 + v87[1]) > 0
          && ((1 << *v87) & *((_DWORD *)&qword_4D2060 + ((unsigned __int64)*v87 >> 5))) == 0 )
        {
          sub_41CE10("buy %d\n", robot_id);
          v88 = *(int *)(*((_QWORD *)final_result + 18) + 4i64);
          --*((_DWORD *)&qword_4D2220 + v88);
          robot_id = *final_result;
          if ( *((_BYTE *)final_result + 120) )
          {
LABEL_128:
            sub_41CE10("buy %d\n", robot_id);
            robot_id = *final_result;
          }
        }
        else if ( *((_BYTE *)final_result + 120) )
        {
          goto LABEL_128;
        }
      }
      sub_4016F0("forward %d %f\n", robot_id, *((_QWORD *)final_result + 13));
      sub_401740("rotate %d %f\n", *final_result, *((_QWORD *)final_result + 14));
      final_result += 42;
    }
    while ( v85 != final_result );
  }
  j_free(Block);
  if ( v108[0] )
    j_free(v108[0]);
  if ( v106[0] )
    j_free(v106[0]);
}