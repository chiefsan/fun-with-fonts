from PIL import Image
im = Image.open('font.png', 'r')
pix_val = list(im.getdata())
pix_val_flat = [x for sets in pix_val for x in sets]
w, h = im.size
for i in range(len(pix_val)):
    pix_val[i] = int(round(sum(pix_val[i]) / float(len(pix_val[i]))))
import numpy as np
pix_val = np.array(pix_val)
pix_val = pix_val.reshape(512, 512)
np.savetxt("font.txt", pix_val, delimiter=" ")
