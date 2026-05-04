#!/bin/bash
[ $# -lt 3 ] && echo "Usage: $0 <client> <port> <image> [x] [y]" && exit 1
CLIENT="$1"
PORT="$2"
X=${4:-0}; Y=${5:-0}

send() {
    while IFS=' ' read -r x y r g b; do
        [[ "$x" == \#* || -z "$x" ]] && continue
        $CLIENT $PORT $((x+X)) $((y+Y)) $r $g $b
    done
}

case "${3##*.}" in
    pxl) send < "$3" ;;
    *)   send < <(python3 -c "
from PIL import Image
img=Image.open('$3').convert('RGB')
for y in range(img.height):
 for x in range(img.width):
  r,g,b=img.getpixel((x,y))
  if not(r>250 and g>250 and b>250):print(x,y,r,g,b)
") ;;
esac
