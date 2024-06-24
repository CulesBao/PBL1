import numpy as np
from PIL import Image
from sklearn.decomposition import PCA

# Đọc dữ liệu từ tệp văn bản
data = np.loadtxt('data_img.txt')

# Áp dụng PCA để giảm chiều dữ liệu xuống còn 2 chiều
pca = PCA(n_components=2)
transformed_data = pca.fit_transform(data)

# Chuẩn hóa dữ liệu về phạm vi từ 0 đến 1 để phù hợp với giá trị pixel
transformed_data -= np.min(transformed_data, axis=0)
transformed_data /= np.max(transformed_data, axis=0)

# Tạo một ma trận trống để chứa dữ liệu ảnh
image_data = np.zeros((100, 100, 3), dtype=np.uint8)

# Đặt giá trị pixel cho từng điểm dữ liệu
for i in range(transformed_data.shape[0]):
    x, y = transformed_data[i] * 99  # Scale pixel coordinates to fit the 100x100 image
    x, y = int(x), int(y)  # Convert to integer pixel coordinates
    image_data[y, x] = [255, 255, 255]  # Set pixel value to white

# Tạo ảnh từ dữ liệu và hiển thị hoặc lưu lại
image = Image.fromarray(image_data)
image.show()  # Hiển thị ảnh
image.save('generated_image.png')  # Lưu ảnh

# print("Image saved as generated_image.png")
