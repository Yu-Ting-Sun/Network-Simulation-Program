# Network-Simulation-Program

## 題目
1.	Minium(Threshold):強度夠的時候不切換(Pmin=100dB)
2.	Best_effort:訊號強者提供訊號
3.	Entropy:兩基地台訊號落差值超過閾值時候切換(閾值E=25dB)
4.	自行設定的algo.

根據這四個個別顯示以下題目環境中，車子訊號切換的次數(個別車或總和)

再加上Call Service model，Model模式為:call、Release(訊號不會服務所以不會發生切換)、call、Release….。
* 平均一小時有2call
* 平均每個call時間為3mins
* 程式碼以Normal(又稱高斯) Distribution :N(μ, σ^2)來模擬。
(N(μ, σ^2)來模擬:意思是每通電話不是真的3分鐘整就會掛斷，他是一個分布Normal Distribution，也就是說不定會3分5秒通話也可能2分55之類的)

## 環境
1.地圖:10x10，每格2.5km(也就是該map大小為25x25km)

