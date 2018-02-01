/*
 ***********************************************************************************************************************
 *
 *  Copyright (c) 2014-2018 Advanced Micro Devices, Inc. All Rights Reserved.
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to deal
 *  in the Software without restriction, including without limitation the rights
 *  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *  copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all
 *  copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *  SOFTWARE.
 *
 **********************************************************************************************************************/
#ifndef __VK_SAMPLER_H__
#define __VK_SAMPLER_H__

#pragma once

#include "include/khronos/vulkan.h"
#include "include/vk_defines.h"
#include "include/vk_dispatch.h"
#include "include/vk_utils.h"

#include "palUtil.h"

namespace vk
{

// Forward declare Vulkan classes used in this file
class Device;
class DispatchableSampler;

class Sampler : public NonDispatchable<VkSampler, Sampler>
{
public:
    static VkResult Create(
        Device*                         pDevice,
        const VkSamplerCreateInfo*      pCreateInfo,
        const VkAllocationCallbacks*    pAllocator,
        VkSampler*                      pSampler);

    VK_FORCEINLINE const void* Descriptor(int32_t idx = DefaultDeviceIndex) const
    {
        VK_ASSERT((idx >= 0) && (idx < static_cast<int32_t>(MaxPalDevices)));

        const void* pSrd = static_cast<const void*>(this + 1);

        return Util::VoidPtrInc(pSrd, m_SrdSize * idx);
    }

    VkResult Destroy(
        const Device*                   pDevice,
        const VkAllocationCallbacks*    pAllocator);

protected:
    Sampler(Device* pDevice, uint32_t srdSize)
    :
    m_SrdSize(srdSize)
    {
    }

    uint32_t m_SrdSize;
};

namespace entry
{
VKAPI_ATTR void VKAPI_CALL vkDestroySampler(
    VkDevice                                    device,
    VkSampler                                   sampler,
    const VkAllocationCallbacks*                pAllocator);
} // namespace entry

} // namespace vk

#endif /* __VK_SAMPLER_H__ */