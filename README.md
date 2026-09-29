# fdf · 42 Seoul

> 높이값 격자로 된 `.fdf` 맵 파일을 읽어 등각 투영(isometric) 와이어프레임으로 그리는 과제

## 개요
맵의 각 숫자를 (x, y) 격자 위의 높이 z로 해석하고, 3D 점들을 2D 화면에 투영한 뒤 이웃한 점끼리 선으로 이어 창에 출력한다.
그래픽 출력은 42의 minilibx(macOS용, `mlx/` 폴더의 Swift 기반 `libmlx.dylib`)를 사용한다.

## 구현 포인트
- **맵 파싱과 검증**: `get_next_line`으로 줄 단위로 읽어 연결 리스트에 담고(`fdf_file_open`), 공백으로 나눠 2차원 리스트로 만든다(`ft_split_space`). 행마다 열 개수가 같은지(`lst_column_check`), 숫자 형식인지, int 범위인지 검사한다. 확장자는 `.fdf`만 받는다. `,` 뒤의 색상 값은 잘라내고(`remove_char_lst`) 모든 선은 흰색(`WHITE`)으로 그린다.
- **등각 투영**: `xyz_change_isometric_coodinate`에서
  `x' = cos30° · (x - y)`, `y' = 0.5 · (x + y) - z · zratio`
  로 변환한다. `zratio`는 계산된 스케일에 따라 8 또는 1로 정해진다(`vector_setting_for_render`).
- **자동 스케일·중앙 정렬**: `get_scale_point`가 맵의 세 모서리 점을 z=0으로 투영해 그림 크기를 구하고, 1920×1080 창에 맞는 배율을 계산한다. 이후 `vector_move_in_window`가 그림이 창 가운데 오도록 모든 점을 평행 이동한다.
- **선 그리기 (Bresenham 방식)**: `dot_on_pixel`이 기울기에 따라 x축 기준(`x_plus_pixel_put`) 또는 y축 기준(`y_plus_pixel_put`)으로 나누고, 정수 오차 누적(`sum_slope * 2 > delta`)으로 다음 픽셀을 정한다. 픽셀은 이미지 버퍼에 직접 쓰고(`img_pix_put`, 화면 밖 좌표는 무시) 마지막에 한 번 `mlx_put_image_to_window`로 출력한다.
- **렌더링 순서**: `line_draw`가 2차원 배열로 바꾼 맵(`make_map_arry`)을 순회하며 각 점을 오른쪽·아래 이웃과 연결한다.
- **키 조작**: `ESC` 키 또는 창 닫기 버튼으로 이미지·창을 해제하고 종료한다(`mlx_event.c`). 확대·회전 같은 추가 조작은 없다.

## 빌드 & 실행
macOS 환경 기준 (`-framework OpenGL -framework AppKit`, `libmlx.dylib`)
```bash
make
./fdf test_maps/42.fdf
./fdf test_maps/mars.fdf
```

`test_maps/`에 `42.fdf`, `pyramide.fdf`, `mars.fdf`, `julia.fdf`, `elem-col.fdf` 등 테스트 맵이 들어 있다.

## 구조
```
fdf/
├── makefile
├── fdf.h
├── main_test.c              # 진입점: 파싱 -> 변환 -> 그리기 -> 이벤트 루프
├── input.c                  # 인자·확장자 검사, 파일 읽기
├── map_check.c map_check2.c # 맵 형식 검증, 문자열 -> 정수
├── init.c init2.c           # mlx 초기화, 벡터 리스트 생성
├── scale.c isometric.c      # 배율 계산, 등각 투영
├── move.c                   # 창 중앙 정렬
├── map.c                    # 리스트 -> 2차원 배열
├── line.c                   # 선 그리기, 픽셀 출력
├── mlx_event.c              # ESC / 창 닫기
├── read_line.c read_line2.c # get_next_line
├── utils.c utils2.c free.c print.c
├── test_maps/               # 예제 .fdf 맵
├── libft/                   # 직접 구현한 libft
└── mlx/                     # minilibx (macOS)
```

42 Seoul 공통 과정 과제.
