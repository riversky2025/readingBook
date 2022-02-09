#  安装多环境

## python环境安装

```
conda create --name py36hongyi python=3.6 
activate py36hongyi  # windows
source activate py36hongyi # linux/mac

conda info --envs  #查看安装的信息
```

##  换源

```
conda config --add channels https://mirrors.tuna.tsinghua.edu.cn/anaconda/pkgs/free/
conda config --set show_channel_urls yes


切回默认
conda config --remove-key channels
```



查询cuda 版本

```
nvcc --version
```

## 安装pytorch

```
https://pytorch.org/get-started/locally/

conda install pytorch torchvision torchaudio cudatoolkit=10.2 -c pytorch
```

