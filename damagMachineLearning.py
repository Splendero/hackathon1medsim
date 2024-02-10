import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.linear_model import LinearRegression
from sklearn.metrics import mean_squared_error
 
# Step 1: Read the CSV file
data = pd.read_csv("training_data.csv")
 
# Step 2: Split the data into input features (X) and target variable (y)
X = data.drop(columns=["Damage"])  # Features
y = data["Damage"]  # Target variable
 
# Step 3: Train-test split
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)
 
# Step 4: Train a regression model
model = LinearRegression()
model.fit(X_train, y_train)
 
# Step 5: Evaluate the model
train_predictions = model.predict(X_train)
train_rmse = mean_squared_error(y_train, train_predictions, squared=False)
print("Training RMSE:", train_rmse)
 
test_predictions = model.predict(X_test)
test_rmse = mean_squared_error(y_test, test_predictions, squared=False)
print("Testing RMSE:", test_rmse)